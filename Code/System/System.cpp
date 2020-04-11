/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "StdAfx.h"
#include "System.h"

#include <IInput.h>
#include <Physics/IPhysics.h>
#include <Renderer/IRenderer.h>
#include <IGame.h>

#include "Log.h"
#include "FileManager.h"
#include "EntitySystem/EntitySystem.h"

#include <string>
#include <memory>
#include <chrono>
#include <future>

#ifdef _WIN32
#else
#include <dlfcn.h>
#endif

extern "C"
{
	API_EXPORT ISystem* CreateSystemInterface()
	{
		ISystem* pSystem = new CSystem();

		pSystem->InitializeModule();

		return pSystem;
	}
}

/////////////////////////////////////////////////
CSystem::CSystem()
	: m_isQuit(false)
	, m_pFileManager(nullptr)
	, m_pWindowManager(nullptr)
	, m_pEntitySystem(nullptr)
	, m_pRenderer(nullptr)
	, m_pLogger(nullptr)
	, m_pInput(nullptr)
	, m_pPhysics(nullptr)
	, m_pGame(nullptr)
	, m_nrOfFrames(0)
	, m_beginSec(0.f)
	, m_avgFps(0.f)
	, m_systemText(nullptr)
{
}

/////////////////////////////////////////////////
void CSystem::InitializeModule()
{
	m_pLogger = std::make_unique<CLog>();
	m_pFileManager = std::make_unique<CFileManager>(this);

	m_pWindowManager = std::make_unique<CWindowManager>(this);
	m_pWindowManager->initWindow(EWindowType::eWT_SDL2);
	m_pWindowManager->registerWindowEvents(this);

	m_pEntitySystem = std::make_unique<CEntitySystem>(this);

	m_pRenderer = std::unique_ptr<IRenderer>(LoadModule<IRenderer>(SCreateModuleParams<ERenderer>{ ERenderer::SDL2 }));
	m_pInput = std::unique_ptr<IInput>(LoadModule<IInput>(SCreateModuleParams<EInput>{ EInput::SDL2 }));
	m_pPhysics = std::unique_ptr<IPhysics>(LoadModule<IPhysics>(SCreateModuleParams<EPhysics>{ EPhysics::SDL2 }));
	m_pGame = std::unique_ptr<IGame>(LoadModule<IGame>());

	m_beginSec = getTime();

	while (!m_isQuit)
	{
		onUpdate();
	}
}

/////////////////////////////////////////////////
void CSystem::onUpdate()
{
	// Update Window Manager
	m_pWindowManager->onUpdate();

	// Update Input
	GetInput()->onUpdate();

	// Update Physics
	GetPhysics()->onUpdate();

	// Update Entity System
	GetEntitySystem()->onUpdate();

	m_avgFps = m_nrOfFrames / ((getTime() - m_beginSec));

	// Update Renderer
	GetRenderer()->onUpdate();

	// Update Game
	m_pGame->onUpdate();

	++m_nrOfFrames;

	updateSystemInfo();
}

/////////////////////////////////////////////////
void CSystem::unregisterWindowEvents(IWindowEventListener * listener)
{
	m_pWindowManager->unregisterWindowEvents(listener);
}

/////////////////////////////////////////////////
float CSystem::getTime() const
{
	return std::chrono::duration_cast<std::chrono::duration<float>>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

/////////////////////////////////////////////////
void CSystem::registerWindowEvents(IWindowEventListener * listener)
{
	m_pWindowManager->registerWindowEvents(listener);
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

/////////////////////////////////////////////////
void CSystem::updateSystemInfo()
{
	std::string systemText = "   " + std::to_string(static_cast<int>(m_avgFps)) + " FPS "
		+ "/ Active Entities: " + std::to_string(GetEntitySystem()->getEntityCount())
		+ " / CamPos: " + std::to_string(GetRenderer()->GetCamera()->GetPosition().x) 
		+ "," + std::to_string(GetRenderer()->GetCamera()->GetPosition().y);

	if (!m_systemText)
	{
		STextParams params;
		params.layerId = INT_MAX;
		params.text = systemText;
		params.fontSize = 25;
		params.position = Vector2(30.f, 5.f);
		params.color = RGBAColor(244, 208, 63, 1);

		m_systemText = static_cast<IText*>(GetRenderer()->CreateRenderObject(params));
		m_systemText->setRenderActive(true);
	}
	else
	{
		m_systemText->setText(systemText);
	}
}

/////////////////////////////////////////////////
template <typename ModuleType, typename ParamsType>
ModuleType * CSystem::LoadModule(SCreateModuleParams<ParamsType> createParams)
{
	IModule* pModule = nullptr;
	std::string moduleNameStr = "";

	if (std::is_same<ModuleType, IRenderer>::value) { moduleNameStr = "Renderer"; }
	else if (std::is_same<ModuleType, IInput>::value) { moduleNameStr = "Input"; }
	else if (std::is_same<ModuleType, IPhysics>::value) { moduleNameStr = "Physics"; }
	else if (std::is_same<ModuleType, IGame>::value) { moduleNameStr = "Game"; }

#ifdef _WIN32
	moduleNameStr += ".dll";
	auto lib = LoadLibrary(moduleNameStr.c_str());
	typedef IModule*(*FNPTR)(ISystem* systemContext, SCreateModuleParams<ParamsType> params);
	FNPTR CreateModuleInterface = (FNPTR)GetProcAddress(lib, "CreateModuleInterface");

	if (!CreateModuleInterface)
		GetLogger()->Log(("Cannot find " + moduleNameStr).c_str());
	else
		pModule = CreateModuleInterface(this, createParams);

#else
	moduleNameStr = "libBok" + moduleNameStr + ".so";
	auto lib = dlopen(moduleNameStr.c_str(), RTLD_GLOBAL);
	typedef IModule* (*func_ptr_t)(ISystem*, SCreateModuleParams<ParamsType>);
	func_ptr_t CreateModuleInterface = (func_ptr_t)dlsym(lib, "CreateModuleInterface");

	if (!CreateModuleInterface)
		GetLogger()->Log(("Cannot find " + moduleNameStr).c_str());
	else
		pModule = CreateModuleInterface(this, createParams);

#endif

	if(pModule)
		GetLogger()->Log(("Module " + moduleNameStr + " loaded.").c_str());
	else
		GetLogger()->Log(("Failed to load module " + moduleNameStr).c_str());

	return static_cast<ModuleType*>(pModule);
}