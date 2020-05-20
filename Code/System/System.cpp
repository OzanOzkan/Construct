#include "StdAfx.h"
#include "System.h"

#include <IInput.h>
#include <Physics/IPhysics.h>
#include <Renderer/IRenderer.h>
#include <IGame.h>

#include <string>
#include <memory>
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

		return pSystem;
	}
}

/////////////////////////////////////////////////
CSystem::CSystem()
	: m_isQuit(false)
	, m_pRenderTarget(nullptr)
	, m_pFileManager(nullptr)
	, m_pWindowManager(nullptr)
	, m_pEntitySystem(nullptr)
	, m_pLevelSystem(nullptr)
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
	m_pTime = std::make_unique<CTime>();

	m_pWindowManager = std::make_unique<CWindowManager>(this);
	m_pWindowManager->initWindow(EWindowType::eWT_SDL2, m_pRenderTarget);
	m_pWindowManager->registerWindowEvents(this);

	m_pEntitySystem = std::make_unique<CEntitySystem>(this);
	m_pLevelSystem = std::make_unique<CLevelSystem>(this);

	m_pRenderer = std::unique_ptr<IRenderer>(LoadModule<IRenderer>(SCreateModuleParams<ERenderer>{ ERenderer::SDL2 }));
	m_pInput = std::unique_ptr<IInput>(LoadModule<IInput>(SCreateModuleParams<EInput>{ EInput::SDL2 }));
	m_pPhysics = std::unique_ptr<IPhysics>(LoadModule<IPhysics>(SCreateModuleParams<EPhysics>{ EPhysics::BOX2D }));
	m_pGame = std::unique_ptr<IGame>(LoadModule<IGame>());

	m_beginSec = m_pTime->GetSystemTime();

	while (!m_isQuit)
	{
		onPreUpdate();
		onUpdate();
		onPostUpdate();
	}
}

/////////////////////////////////////////
void CSystem::onPreUpdate()
{
	m_pTime->onPreUpdate();

	m_pWindowManager->onPreUpdate();

	m_pInput->onPreUpdate();

	m_pPhysics->onPreUpdate();

	m_pEntitySystem->onPreUpdate();

	m_pRenderer->onPreUpdate();

	m_pGame->onPreUpdate();

}

/////////////////////////////////////////////////
void CSystem::onUpdate()
{
	// Update Window Manager
	m_pWindowManager->onUpdate();

	// Update Input
	m_pInput->onUpdate();

	// Update Physics
	m_pPhysics->onUpdate();

	// Update Entity System
	m_pEntitySystem->onUpdate();

	m_avgFps = m_nrOfFrames / ((m_pTime->GetSystemTime() - m_beginSec));

	// Update Renderer
	m_pRenderer->onUpdate();

	// Update Game
	m_pGame->onUpdate();

	++m_nrOfFrames;

	updateSystemInfo();
}

/////////////////////////////////////////
void CSystem::onPostUpdate()
{
	m_pWindowManager->onPostUpdate();

	m_pInput->onPostUpdate();

	m_pPhysics->onPostUpdate();

	m_pEntitySystem->onPostUpdate();

	m_pRenderer->onPostUpdate();

	m_pGame->onPostUpdate();
}

/////////////////////////////////////////
void CSystem::unregisterWindowEvents(IWindowEventListener * listener)
{
	m_pWindowManager->unregisterWindowEvents(listener);
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
	std::string systemText = std::to_string(static_cast<int>(m_avgFps)) + " FPS \n"
		+ "Delta Time: " + std::to_string(m_pTime->GetDeltaTime()) + " secs \n"
		+ "Active Entities: " + std::to_string(GetEntitySystem()->getEntityCount()) + "\n"
		+ "Loaded Textures: " + std::to_string(GetRenderer()->GetTextureManager()->getLoadedTextureCount()) + "\n"
		+ "CamPos: " + std::to_string(GetRenderer()->GetCamera()->GetPosition().x) + "," + std::to_string(GetRenderer()->GetCamera()->GetPosition().y) + "\n"
		+ "Current Level: " + GetLevelSystem()->getCurrentLevelName();

	if (!m_systemText)
	{
		STextParams params;
		params.layerId = std::numeric_limits<int>::max();
		params.text = systemText;
		params.fontSize = 26;
		params.position = Vector2(30.f, 30.f);
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