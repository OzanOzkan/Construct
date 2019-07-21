#pragma once

#include <ISystem.h>
#include <IRenderer.h>
#include "Window/Window.h"

#include <memory>

class CRenderer : public IRenderer, public IWindowEventListener
{
public:
	CRenderer(SEnvironment* env);
	virtual ~CRenderer();

	// IModule
	virtual void InitializeModule() override;
	virtual void Update() override;
	// ~IModule

	// IWindowEventListener
	virtual void onWindowEvent(const int& key, const int& action) override;
	// ~IWindowEventListener

	virtual bool TestRendererModule() override { return true; }

private:
	void initWindow();

private:
	std::unique_ptr<CWindow> m_window;
	SEnvironment* m_pEnv;
};