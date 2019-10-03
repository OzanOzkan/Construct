/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "System.h"

#include "Log.h"
#include "FileManager.h"
#include "EntitySystem/EntitySystem.h"
#include <IRenderer.h>
#include <IInput.h>

#include <string>
#include <memory>
#include <chrono>
#include <future>

extern "C"
{
	API_EXPORT ISystem* CreateSystemInterface()
	{
		std::unique_ptr<CSystem> pSystem = std::make_unique<CSystem>();

		return pSystem.release();
	}
}

/////////////////////////////////////////////////
CSystem::CSystem()
{
}

/////////////////////////////////////////////////
CSystem::~CSystem()
{
}

/////////////////////////////////////////////////
void CSystem::InitializeModule()
{
	/*
		SUBJECT TO CHANGE: Temporary implementation.
	*/

	m_env.pSystem = this;

	std::unique_ptr<CLog> logger = std::make_unique<CLog>();
	m_env.pLog = logger.release();

	m_fileManager = std::make_unique<CFileManager>(&m_env);

	m_windowManager = std::make_unique<CWindowManager>(&m_env);
	m_windowManager->initWindow(EWindowType::eWT_SDL2);
	m_windowManager->registerWindowEvents(this);

	CreateModuleInstance(EModule::eM_RENDERER);
	CreateModuleInstance(EModule::eM_INPUT);

	m_windowManager->registerWindowEvents(this);

	std::unique_ptr<CEntitySystem> entitySystem = std::make_unique<CEntitySystem>();
	m_env.pEntitySystem = entitySystem.release();

	CreateModuleInstance(EModule::eM_GAME);

	while (!m_isQuit)
	{
		onUpdate();
	}
}

/////////////////////////////////////////////////
void CSystem::onUpdate()
{
	m_windowManager->onUpdate();
	m_env.pRenderer->onUpdate();
	m_env.pInput->onUpdate();
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
		typedef IRenderer*(*FNPTR)(SEnvironment* env);
		FNPTR CreateModuleInterface = (FNPTR)GetProcAddress(lib, "CreateModuleInterface");

		if (!CreateModuleInterface) {
			GetEnvironment()->pLog->Log("Cannot find Renderer.dll");
		}
		else
		{
			if (m_env.pRenderer = CreateModuleInterface(&m_env))
			{
				std::string logText = { "Module: Renderer: " };
				logText += (GetEnvironment()->pRenderer->TestRendererModule() ? "OK" : "FAIL");
				GetEnvironment()->pLog->Log(logText.c_str());
			}

		}
	}
	break;
	case EModule::eM_INPUT:
	{
		auto lib = LoadExternalLibrary("Input.dll");
		typedef IInput*(*FNPTR)(SEnvironment* env);
		FNPTR CreateInputInterface = (FNPTR)GetProcAddress(lib, "CreateInputInterface");

		if (!CreateInputInterface) {
			GetEnvironment()->pLog->Log("Cannot find Input.dll");
		}
		else
		{
			if (m_env.pInput = CreateInputInterface(&m_env))
			{
				m_env.pInput->InitializeModule();
				GetEnvironment()->pLog->Log("Module: Input: OK");
			}

		}
	}
	break;
	case EModule::eM_GAME:
	{
		auto lib = LoadExternalLibrary("Game.dll");
		typedef IModule*(*FNPTR)(SEnvironment* env);
		FNPTR CreateGameModule = (FNPTR)GetProcAddress(lib, "CreateGameModule");

		if (!CreateGameModule) {
			GetEnvironment()->pLog->Log("Cannot find Game.dll");
		}
		else
		{
			if (IModule* pModule = CreateGameModule(&m_env))
			{
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
		GetEnvironment()->pLog->Log("CSystem::onWindowEvent(): Window Closed.");
		m_isQuit = true;
	}
}
