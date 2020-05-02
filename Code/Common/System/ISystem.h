/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "IWindowManager.h"
#include "IWindowEventListener.h"
#include "IFileManager.h"

#include <memory>

class ISystem;
class IRenderer;
class ILog;
class IInput;
class IPhysics;
class IGame;
class IWindowEventListener;
class IEntitySystem;

class ISystem : public IModule
{
public:
	// ISystemInterface
	virtual void InitializeModule() = 0;
	virtual void onUpdate() = 0;
	// ~ISystemInterface

	virtual void setRenderTarget(void* renderTarget) = 0;

	// Window
	virtual void registerWindowEvents(IWindowEventListener* listener) = 0;
	virtual void unregisterWindowEvents(IWindowEventListener* listener) = 0;
	virtual IWindowManager* GetWindowManager() = 0;
	// ~Window

	virtual float getTime() const = 0;

	// File Manager
	virtual IFileManager* getFileManager() = 0;

	// Modules
	virtual IRenderer* GetRenderer() = 0;
	virtual ILog* GetLogger() = 0;
	virtual IInput* GetInput() = 0;
	virtual IPhysics* GetPhysics() = 0;
	virtual IEntitySystem* GetEntitySystem() = 0;
};