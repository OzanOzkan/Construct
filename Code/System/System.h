#pragma once

#include <System/ISystem.h>
#include <Renderer/IRenderObject.h>
#include <System/IWindowEventListener.h>
#include "Window/WindowManager.h"
#include "LevelSystem/LevelSystem.h"
#include "FileSystem/FileManager.h"
#include "EntitySystem/EntitySystem.h"
#include "Log.h"
#include "Time.h"

#include <memory>
#include <string>

class CSystem : public ISystem, IWindowEventListener {

public:
	CSystem();

	// ISystemInterface
	void InitializeModule() override;
	// ~ISystemInterface

	void setRenderTarget(void* renderTarget) override { m_pRenderTarget = renderTarget; }

	// Modules
	IRenderer* GetRenderer() override { return m_pRenderer.get(); }
	ILog* GetLogger() override { return m_pLogger.get(); }
	IInput* GetInput() override { return m_pInput.get(); }
	IPhysics* GetPhysics() override { return m_pPhysics.get(); }
	IEntitySystem* GetEntitySystem() override { return m_pEntitySystem.get(); }
	IWindowManager* GetWindowManager() override { return m_pWindowManager.get(); }
	IFileManager* getFileManager() override { return m_pFileManager.get(); }
	ILevelSystem* GetLevelSystem() override { return m_pLevelSystem.get(); }

	ITime* GetTime() override { return m_pTime.get(); }
	
	// !Subject to change
	void registerWindowEvents(IWindowEventListener* listener) override;
	void unregisterWindowEvents(IWindowEventListener* listener) override;
	void updateSystemInfo();
	// ~!Subject to change

private:
	// IWindowEventListener
	void onWindowEvent(const SWindowEvent & event) override;
	// ~IWindowEventListener

	void onPreUpdate() override;
	void onUpdate() override;
	void onPostUpdate() override;

	template <typename ModuleType, typename ParamsType = int>
	ModuleType* LoadModule(SCreateModuleParams<ParamsType> createParams = {});

private:
	bool m_isQuit = false;
	void* m_pRenderTarget = nullptr;

	std::unique_ptr<CFileManager> m_pFileManager = nullptr;
	std::unique_ptr<CWindowManager> m_pWindowManager = nullptr;

	std::unique_ptr<IRenderer> m_pRenderer = nullptr;
	std::unique_ptr<CLog> m_pLogger = nullptr;
	std::unique_ptr<IInput> m_pInput = nullptr;
	std::unique_ptr<IPhysics> m_pPhysics = nullptr;
	std::unique_ptr<IGame> m_pGame = nullptr;
	std::unique_ptr<CEntitySystem> m_pEntitySystem = nullptr;
	std::unique_ptr<CLevelSystem> m_pLevelSystem = nullptr;

	std::unique_ptr<CTime> m_pTime = nullptr;

	int m_nrOfFrames = 0;
	int m_beginSec = 0.f;
	float m_avgFps = 0.f;
	IText* m_systemText = nullptr;
};