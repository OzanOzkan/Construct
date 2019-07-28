#pragma once

#include "Core.h"
#include "IModule.h"
#include "IWindowEventListener.h"

class ISystem;
class IRenderer;
class ILog;
class IInput;
class IWindowEventListener;

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

	virtual void RegisterWindowEvents(IWindowEventListener* listener) = 0;
	
	virtual SEnvironment* GetEnvironment() = 0;
};