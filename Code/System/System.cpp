#include "System.h"

#include "Log.h"
#include <IRenderer.h>
#include <Platform.h>

#include <string>
#include <memory>

extern "C"
{
	EXTERN_LIBRARY_EXPORT ISystem* CreateSystemInterface()
	{
		std::unique_ptr<CSystem> pSystem = std::make_unique<CSystem>();

		return pSystem.release();
	}
}

CSystem::CSystem()
{
}

CSystem::~CSystem()
{
}

void CSystem::InitializeModule()
{
	m_env.pSystem = this;

	std::unique_ptr<CLog> logger = std::make_unique<CLog>();
	m_env.pLog = logger.release();

	gEnv = &m_env;

	CreateModuleInstance(EModule::eM_RENDERER);

	while (!m_isQuit)
	{
		Update();
	}
}

void CSystem::Update()
{
	gEnv->pRenderer->Update();
}

void CSystem::CreateModuleInstance(const EModule & moduleName)
{
	switch (moduleName)
	{
	case EModule::eM_RENDERER:
	{
		auto lib = LoadExternalLibrary("Renderer.dll");
		typedef IRenderer*(*FNPTR)(SGlobalEnvironment&);
		FNPTR CreateModuleInterface = (FNPTR)GetProcAddress(lib, "CreateModuleInterface");

		if (!CreateModuleInterface) {
			gEnv->pLog->Log("Cannot find Renderer.dll");
		}
		else
		{
			if (IRenderer* pRenderer = CreateModuleInterface(m_env))
			{
				std::string logText = { "Module Renderer: " };
				logText += (gEnv->pRenderer->TestRendererModule() ? "OK" : "FAIL");
				gEnv->pLog->Log(logText.c_str());
			}

		}
	}
	break;
	}
}
