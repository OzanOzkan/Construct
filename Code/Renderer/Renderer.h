#pragma once

#include <System/ISystem.h>
#include <IRenderer.h>

#include <memory>

class CRenderer : public IRenderer
{
public:
	CRenderer(SEnvironment* env);
	virtual ~CRenderer();

	// IModule
	virtual void InitializeModule() override;
	virtual void Update() override;
	// ~IModule

	virtual bool TestRendererModule() override { return true; }

private:
	SEnvironment* m_pEnv;
};