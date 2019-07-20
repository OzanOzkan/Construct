#pragma once

#include "IModule.h"

#define EXTERN_LIBRARY_EXPORT __declspec(dllexport)
#define EXTERN_LIBRARY_IMPORT __declspec(dllimport)

class ISystem;
class IRenderer;
class ILog;

struct SGlobalEnvironment
{
	ISystem*		pSystem;
	IRenderer*		pRenderer;
	ILog*			pLog;
};

extern "C"
{
	EXTERN_LIBRARY_EXPORT ISystem* CreateSystemInterface();
}

class ISystem : public IModule
{
public:
	virtual ~ISystem(){}

	// ISystemInterface
	virtual void InitializeModule() = 0;
	virtual void Update() = 0;
	// ~ISystemInterface

	//virtual SGlobalEnvironment* getGlobalEnvironment() = 0;
};

extern SGlobalEnvironment* gEnv;