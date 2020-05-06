#pragma once

#include <System/ISystem.h>
#include <System/IWindowEventListener.h>
#include "Window/WindowManager.h"

#include <Renderer/IRenderObject.h>

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
	
	// !Subject to change
	void registerWindowEvents(IWindowEventListener* listener) override;
	void unregisterWindowEvents(IWindowEventListener* listener) override;
	float getTime() const override;
	void updateSystemInfo();
	// ~!Subject to change

private:
	// IWindowEventListener
	void onWindowEvent(const SWindowEvent & event) override;
	// ~IWindowEventListener

	void onUpdate() override;

	template <typename ModuleType, typename ParamsType = int>
	ModuleType* LoadModule(SCreateModuleParams<ParamsType> createParams = {});

private:
	bool m_isQuit = false;
	void* m_pRenderTarget = nullptr;

	std::unique_ptr<IFileManager> m_pFileManager = nullptr;
	std::unique_ptr<CWindowManager> m_pWindowManager = nullptr;

	std::unique_ptr<IRenderer> m_pRenderer = nullptr;
	std::unique_ptr<ILog> m_pLogger = nullptr;
	std::unique_ptr<IInput> m_pInput = nullptr;
	std::unique_ptr<IPhysics> m_pPhysics = nullptr;
	std::unique_ptr<IGame> m_pGame = nullptr;
	std::unique_ptr<IEntitySystem> m_pEntitySystem = nullptr;
	std::unique_ptr<ILevelSystem> m_pLevelSystem = nullptr;

	int m_nrOfFrames = 0;
	int m_beginSec = 0.f;
	float m_avgFps = 0.f;
	IText* m_systemText = nullptr;
};