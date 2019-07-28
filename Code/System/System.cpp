#include "System.h"

#include "Log.h"
#include <IRenderer.h>
#include <IInput.h>
#include <Core.h>

#include "Window/WindowManager.h"

#include <string>
#include <memory>

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
	m_env.pSystem = this;

	std::unique_ptr<CLog> logger = std::make_unique<CLog>();
	m_env.pLog = logger.release();

	m_windowManager = std::make_unique<CWindowManager>();
	m_windowManager->initWindow();
	m_windowManager->addEventListener(this);

	CreateModuleInstance(EModule::eM_RENDERER);
	CreateModuleInstance(EModule::eM_INPUT);

	while (!m_isQuit)
	{
		Update();
	}
}

/////////////////////////////////////////////////
void CSystem::Update()
{
	GetEnvironment()->pRenderer->Update();
	GetEnvironment()->pInput->Update();

	m_windowManager->onUpdate();
}

/////////////////////////////////////////////////
void CSystem::CreateModuleInstance(const EModule & moduleName)
{
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
				GetEnvironment()->pLog->Log("Module: Input: OK");
			}

		}
	}
	break;
	}
}

void CSystem::onWindowEvent(const SWindowEvent & event)
{
	std::string logMsg = "CSystem::onWindowEvent(): ";
	if (event.event_type == EWindowEventType::eWE_KEY_PRESSED) logMsg += " eWE_KEY_PRESSED";

	GetEnvironment()->pLog->Log(logMsg.c_str());
}
