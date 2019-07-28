#pragma once

#include "Core.h"
#include "IModule.h"

class IRenderer : IModule
{
public:
	virtual ~IRenderer() {}

	// IModule
	virtual void InitializeModule() = 0;
	virtual void Update() = 0;
	// ~IModule

	virtual bool TestRendererModule() = 0;
};

extern "C"
{
	API_EXPORT IRenderer* CreateModuleInterface(SEnvironment *env);
}