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

	// Inherited via IWindowEventListener
	virtual void onWindowEvent(const SWindowEvent & event) override;

	virtual void Update() override;
	virtual SEnvironment* GetEnvironment() override { return &m_env; }
	virtual IWindowManager* GetWindowManager() const { return m_windowManager.get(); }

	void CreateModuleInstance(const EModule& moduleName);

private:
	SEnvironment m_env;
	bool m_isQuit = false;

	std::unique_ptr<IWindowManager> m_windowManager = nullptr;
};