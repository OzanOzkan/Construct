#pragma once

#include "Core.h"
#include "IModule.h"

class ISystem;
class IRenderer;
class ILog;
class IInput;

struct SEnvironment
{
	ISystem*		pSystem;
	IRenderer*		pRenderer;
	ILog*			pLog;
	IInput*			pInput;
};

extern "C"
{
	API_EXPORT ISystem* CreateSystemInterface();
}

class ISystem : public IModule
{
public:
	virtual ~ISystem(){}

	// ISystemInterface
	virtual void InitializeModule() = 0;
	virtual void Update() = 0;
	// ~ISystemInterface
	
	virtual SEnvironment* GetEnvironment() = 0;
};