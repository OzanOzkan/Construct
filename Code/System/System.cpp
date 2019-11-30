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

extern "C"
{
	API_EXPORT ISystem* CreateSystemInterface()
	{
		ISystem* pSystem = new CSystem();

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

	m_windowManager->registerWindowEvents(this);

	m_pEntitySystem = std::make_unique<CEntitySystem>(this);

	CreateModuleInstance(EModule::eM_GAME);

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
	GetRenderer()->onUpdate();
	GetInput()->onUpdate();

	GetEntitySystem()->onUpdate();
}

/////////////////////////////////////////////////
void CSystem::CreateModuleInstance(const EModule & moduleName)
{
	/*
		SUBJECT TO CHANGE: Temporary function.
	*/
	
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
		typedef IInput*(*FNPTR)(ISystem* systemContext);
		FNPTR CreateInputInterface = (FNPTR)GetProcAddress(lib, "CreateInputInterface");

		if (!CreateInputInterface) {
			GetLogger()->Log("Cannot find Input.dll");
		}
		else {
			if (m_pInput = std::unique_ptr<IInput>(CreateInputInterface(this))) {
				GetInput()->InitializeModule();
				GetLogger()->Log("Module: Input: OK");
			}
		}
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
