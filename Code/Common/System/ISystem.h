/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "IWindow.h"
#include "IWindowEventListener.h"
#include "IFileManager.h"

class ISystem;
class IRenderer;
class ILog;
class IInput;
class IWindowEventListener;
class IEntitySystem;

struct SEnvironment
{
	ISystem*		pSystem;
	IRenderer*		pRenderer;
	ILog*			pLog;
	IInput*			pInput;
	IEntitySystem*	pEntitySystem;
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
	virtual void onUpdate() = 0;
	// ~ISystemInterface

	virtual SEnvironment* GetEnvironment() = 0;

	// Window
	virtual void registerWindowEvents(IWindowEventListener* listener) = 0;
	virtual void unregisterWindowEvents(IWindowEventListener* listener) = 0;
	virtual WindowProcAddr getWindowProcAddress() = 0;
	// ~Window

	virtual float getTime() const = 0;

	// File Manager
	virtual IFileManager* getFileManager() = 0;
};