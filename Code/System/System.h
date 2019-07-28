#pragma once

#include <System/ISystem.h>
#include "Window/WindowManager.h"
#include <System/IWindowEventListener.h>

#include <memory>

class CSystem : public ISystem, IWindowEventListener {

public:
	CSystem();
	virtual ~CSystem();

	// ISystemInterface
	virtual void InitializeModule() override;
	// ~ISystemInterface

	virtual void Update() override;
	virtual SEnvironment* GetEnvironment() override { return &m_env; }
	virtual void RegisterWindowEvents(IWindowEventListener* listener) override;

	void CreateModuleInstance(const EModule& moduleName);

private:
	SEnvironment m_env;
	bool m_isQuit = false;

	std::unique_ptr<CWindowManager> m_windowManager = nullptr;

	// Inherited via IWindowEventListener
	virtual void onWindowEvent(const SWindowEvent & event) override;
};