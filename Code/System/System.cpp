/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "StdAfx.h"
#include "System.h"

#include "Log.h"
#include "FileManager.h"
#include "EntitySystem/EntitySystem.h"
#include <Renderer/IRenderer.h>
#include <IInput.h>

#include <string>
#include <memory>
#include <chrono>
#include <future>

#include <SDL.h>

#ifdef _WIN32
#else
#include <dlfcn.h>
#endif

extern "C"
{
	API_EXPORT ISystem* CreateSystemInterface(std::string libDir)
	{
		ISystem* pSystem = new CSystem(libDir);
		pSystem->InitializeModule();

		return pSystem;
	}
}

/////////////////////////////////////////////////
void CSystem::InitializeModule()
{
	/*
		SUBJECT TO CHANGE: Temporary implementation.
	*/

	m_pLogger = std::make_unique<CLog>();
	m_fileManager = std::make_unique<CFileManager>(this);

	m_windowManager = std::make_unique<CWindowManager>(this);
	m_windowManager->initWindow(EWindowType::eWT_SDL2);
	m_windowManager->registerWindowEvents(this);

	CreateModuleInstance(EModule::eM_RENDERER);
	CreateModuleInstance(EModule::eM_INPUT);

	//m_windowManager->registerWindowEvents(this);

	m_pEntitySystem = std::make_unique<CEntitySystem>(this);

	CreateModuleInstance(EModule::eM_GAME);

	m_beginSec = getTime();
	//m_beginSec = m_windowManager->getTicks();

	while (!m_isQuit)
	{
		onUpdate();
	}
}

/////////////////////////////////////////////////
void CSystem::onUpdate()
{
	// Make system event listener.
	m_windowManager->onUpdate();

	GetInput()->onUpdate();

	GetEntitySystem()->onUpdate();

	m_avgFps = m_nrOfFrames / ((getTime() - m_beginSec));

	GetRenderer()->onUpdate();

	++m_nrOfFrames;

	updateFPSCounter();
}

/////////////////////////////////////////////////
void CSystem::CreateModuleInstance(const EModule & moduleName)
{
	/*
		SUBJECT TO CHANGE: Temporary function.
	*/
	
#ifdef _WIN32
	switch (moduleName)
	{
	case EModule::eM_RENDERER:
	{
		auto lib = LoadExternalLibrary("Renderer.dll");
		typedef IRenderer*(*FNPTR)(ISystem* systemContext, ERenderer renderer);
		FNPTR CreateModuleInterface = (FNPTR)GetProcAddress(lib, "CreateModuleInterface");

		if (!CreateModuleInterface)
			GetLogger()->Log("Cannot find Renderer.dll");
		else
			m_pRenderer = std::unique_ptr<IRenderer>(CreateModuleInterface(this, ERenderer::eRDR_SDL2));
	}
	break;
	case EModule::eM_INPUT:
	{
		auto lib = LoadExternalLibrary("Input.dll");
		typedef IInput*(*FNPTR)(ISystem* systemContext, EInput inputInterface);
		FNPTR CreateInputInterface = (FNPTR)GetProcAddress(lib, "CreateInputInterface");

		if (!CreateInputInterface)
			GetLogger()->Log("Cannot find Input.dll");
		else
			m_pInput = std::unique_ptr<IInput>(CreateInputInterface(this, EInput::eINP_SDL2));
	}
	break;
	case EModule::eM_GAME:
	{
		auto lib = LoadExternalLibrary("Game.dll");
		typedef IModule*(*FNPTR)(ISystem* systemContext);
		FNPTR CreateGameModule = (FNPTR)GetProcAddress(lib, "CreateGameModule");

		if (!CreateGameModule) {
			GetLogger()->Log("Cannot find Game.dll");
		}
		else {
			if (IModule* pModule = CreateGameModule(this)) {
				pModule->InitializeModule();
			}
		}
	}
	break;
	}
#else
	switch (moduleName)
	{
	case EModule::eM_RENDERER:
	{
		std::string libDir = m_libDir + "/libBokRenderer.so";
		auto lib = dlopen(libDir.c_str(), RTLD_LAZY);
        if (!lib) {
            SDL_Log("CSystem::CreateModuleInstance:EModule::eM_RENDERER: %s", dlerror());
        }

		typedef IRenderer* (*func_ptr_t)(ISystem*, ERenderer);
		func_ptr_t fptr = (func_ptr_t)dlsym(lib, "CreateModuleInterface");
		m_pRenderer = std::unique_ptr<IRenderer>(static_cast<IRenderer*>(fptr(this, ERenderer::eRDR_SDL2)));

	}
	break;
	case EModule::eM_INPUT:
	{
		std::string libDir = m_libDir + "/libBokInput.so";
		auto lib = dlopen(libDir.c_str(), RTLD_LAZY);
		if (!lib) {
			SDL_Log("CSystem::CreateModuleInstance:EModule::eM_INPUT: %s", dlerror());
		}

		typedef IInput* (*func_ptr_t)(ISystem*, EInput);
		func_ptr_t fptr = (func_ptr_t)dlsym(lib, "CreateInputInterface");

		m_pInput = std::unique_ptr<IInput>(static_cast<IInput*>(fptr(this, EInput::eINP_SDL2)));
	}
	break;
	case EModule::eM_GAME:
	{
		std::string libDir = m_libDir + "/libBokGame.so";
        auto lib = dlopen(libDir.c_str(), RTLD_LAZY);
        if (!lib) {
            SDL_Log("CSystem::CreateModuleInstance:EModule::eM_GAME: %s", dlerror());
        }

        typedef IModule* (*func_ptr_t)(ISystem*);
        func_ptr_t fptr = (func_ptr_t)dlsym(lib, "CreateGameModule");

        IModule* pModule = static_cast<IModule*>(fptr(this));
        pModule->InitializeModule();
	}
	break;
	}
#endif
}

/////////////////////////////////////////////////
void CSystem::unregisterWindowEvents(IWindowEventListener * listener)
{
	m_windowManager->unregisterWindowEvents(listener);
}

float CSystem::getTime() const
{
	return std::chrono::duration_cast<std::chrono::duration<float>>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

/////////////////////////////////////////////////
void CSystem::registerWindowEvents(IWindowEventListener * listener)
{
	m_windowManager->registerWindowEvents(listener);
}

/////////////////////////////////////////////////
void CSystem::onWindowEvent(const SWindowEvent & event)
{
	if (event.event_type == EWindowEventType::eWE_WINDOW_CLOSED)
	{
		GetLogger()->Log("CSystem::onWindowEvent(): Window Closed.");
		m_isQuit = true;
	}
}

void CSystem::updateFPSCounter()
{
	std::string fpsText = std::to_string(static_cast<int>(m_avgFps)) + " FPS";

	if (!m_pFPSText)
	{
		STextCreateParams params;
		params.text = fpsText;

#ifdef _WIN32
		params.font = "F:\\Development\\ProjectO01\\Assets\\Fonts\\ARIAL.TTF";
#else
		params.font = "Fonts/ARIAL.TTF";
#endif
		params.fontSize = 50;
		params.position = Vector2(5.f, 5.f);

		m_pFPSText = static_cast<IText*>(GetRenderer()->CreateRenderObject(params));
		m_pFPSText->setRenderActive(true);
	}
	else
	{
		m_pFPSText->setText(fpsText);
	}
}