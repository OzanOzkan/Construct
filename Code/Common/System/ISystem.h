#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "IWindowManager.h"
#include "IWindowEventListener.h"
#include "IFileManager.h"
#include "ITime.h"

#include <memory>

class ISystem;
class IRenderer;
class ILog;
class IInput;
class IPhysics;
class IGame;
class IWindowEventListener;
class IEntitySystem;
class ILevelSystem;

class ISystem : public IModule
{
public:
	virtual void setRenderTarget(void* renderTarget) = 0;

	// Window
	virtual void registerWindowEvents(IWindowEventListener* listener) = 0;
	virtual void unregisterWindowEvents(IWindowEventListener* listener) = 0;
	virtual IWindowManager* GetWindowManager() = 0;
	// ~Window

	virtual ITime* GetTime() = 0;

	// File Manager
	virtual IFileManager* getFileManager() = 0;

	// Modules
	virtual IRenderer* GetRenderer() = 0;
	virtual ILog* GetLogger() = 0;
	virtual IInput* GetInput() = 0;
	virtual IPhysics* GetPhysics() = 0;
	virtual IEntitySystem* GetEntitySystem() = 0;
	virtual ILevelSystem* GetLevelSystem() = 0;
};