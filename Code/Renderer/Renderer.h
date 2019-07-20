#pragma once

#include <ISystem.h>
#include <IRenderer.h>
#include "Window/Window.h"

#include <memory>

class CRenderer : public IRenderer
{
public:
	CRenderer(SGlobalEnvironment &env);
	virtual ~CRenderer();

	// ISystemInterface
	virtual void InitializeModule() override;
	virtual void Update() override;
	// ~ISystemInterface

	virtual bool TestRendererModule() override { return true; }

private:
	void initWindow();

private:
	std::unique_ptr<CWindow> m_window;
};