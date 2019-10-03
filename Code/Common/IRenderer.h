/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "Core.h"
#include "IModule.h"

class IRenderer : public IModule
{
public:
	virtual ~IRenderer() {}

	// IModule
	virtual void InitializeModule() = 0;
	virtual void onUpdate() = 0;
	// ~IModule

	virtual bool TestRendererModule() = 0;
};

extern "C"
{
	API_EXPORT IRenderer* CreateModuleInterface(SEnvironment *env);
}