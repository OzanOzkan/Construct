#pragma once

#include <System/ISystem.h>
#include <IRenderer.h>
#include <IInput.h>

#include "Shader.h"

#include <memory>

#include "TextRenderer/TextRenderer.h"

class CRenderer : public IRenderer, IWindowEventListener
{
public:
	CRenderer(SEnvironment* env);
	virtual ~CRenderer();

	// IModule
	virtual void InitializeModule() override;
	virtual void onUpdate() override;
	// ~IModule

	virtual bool TestRendererModule() override { return true; }

private:
	// Inherited via IWindowEventListener
	virtual void onWindowEvent(const SWindowEvent & event) override;

private:
	SEnvironment * m_pEnv = nullptr;
	std::unique_ptr<CShader> m_defaultShader = nullptr;

	double tempMouseX = 0;
	double tempMouseY = 0;
	float tempColor = 0.0;

	std::unique_ptr<CTextRenderer> testTextRenderer = nullptr;
};