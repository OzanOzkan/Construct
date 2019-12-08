/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <Core.h>
#include <System/ISystem.h>
#include <System/IWindowEventListener.h>
#include "Window/WindowManager.h"

#include <Renderer/IRenderObject.h>

#include <memory>
#include <string>

class CSystem : public ISystem, IWindowEventListener {

public:
    CSystem(const std::string& libDir) : m_libDir(libDir) {}

	// ISystemInterface
	void InitializeModule() override;
	// ~ISystemInterface

	IFileManager* getFileManager() override { return m_fileManager.get(); }

	// Modules
	IRenderer* GetRenderer() override { return m_pRenderer.get(); }
	ILog* GetLogger() override { return m_pLogger.get(); }
	IInput* GetInput() override { return m_pInput.get(); }
	IEntitySystem* GetEntitySystem() override { return m_pEntitySystem.get(); }
	
	// !Subject to change
	void registerWindowEvents(IWindowEventListener* listener) override;
	void unregisterWindowEvents(IWindowEventListener* listener) override;
	WindowProcAddr getWindowProcAddress() override { return m_windowManager->getWindowProcAddress(); }
	int getWindowId() override { return m_windowManager->getWindowId(); }
	float getTime() const override;
	void updateFPSCounter();
	// ~!Subject to change

private:
	void CreateModuleInstance(const EModule& moduleName);

	// IWindowEventListener
	void onWindowEvent(const SWindowEvent & event) override;
	// ~IWindowEventListener

	void onUpdate() override;

private:
	bool m_isQuit = false;

	std::string m_libDir = "";

	std::unique_ptr<IFileManager> m_fileManager = nullptr;
	std::unique_ptr<CWindowManager> m_windowManager = nullptr;

	std::unique_ptr<IRenderer> m_pRenderer = nullptr;
	std::unique_ptr<ILog> m_pLogger = nullptr;
	std::unique_ptr<IInput> m_pInput = nullptr;
	std::unique_ptr<IEntitySystem> m_pEntitySystem = nullptr;

	int m_nrOfFrames = 0;
	int m_beginSec = 0.f;
	float m_avgFps = 0.f;
	IText* m_pFPSText = nullptr;
};