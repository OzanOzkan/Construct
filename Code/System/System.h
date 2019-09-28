#pragma once

#include <Core.h>
#include <System/ISystem.h>
#include <System/IWindowEventListener.h>
#include "Window/WindowManager.h"

#include <memory>

class CSystem : public ISystem, IWindowEventListener {

public:
	CSystem();
	virtual ~CSystem();

	// ISystemInterface
	virtual void InitializeModule() override;
	// ~ISystemInterface

	virtual SEnvironment* GetEnvironment() override { return &m_env; }
	virtual IFileManager* getFileManager() override { return m_fileManager.get(); }
	
	virtual void registerWindowEvents(IWindowEventListener* listener);
	virtual void unregisterWindowEvents(IWindowEventListener* listener);
	WindowProcAddr getWindowProcAddress() { return m_windowManager->getWindowProcAddress(); }

private:
	void CreateModuleInstance(const EModule& moduleName);

	// IWindowEventListener
	virtual void onWindowEvent(const SWindowEvent & event) override;
	// ~IWindowEventListener

	virtual void onUpdate() override;

private:
	SEnvironment m_env;
	bool m_isQuit = false;

	std::unique_ptr<IFileManager> m_fileManager = nullptr;
	std::unique_ptr<CWindowManager> m_windowManager = nullptr;
};