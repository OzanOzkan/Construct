#pragma once

#include "Core.h"
#include "IModule.h"

#include <set>

enum class EKey
{
	eKI_DUMMY = 0
};

struct SInputEvent
{

};

class InputEventListener
{
public:
	virtual void onInputEvent(const SInputEvent& event) = 0;
};

class IInput : public IModule
{
public:
	virtual ~IInput(){}

	// IModule
	virtual void InitializeModule() = 0;
	virtual void Update() = 0;
	// ~IModule

	virtual void RegisterEventListener(InputEventListener* listener) = 0;
	virtual void RemoveEventListener(InputEventListener* listener) = 0;
	
	virtual void PostInputEvent(const SInputEvent& event) = 0;

	//virtual void IsKeyDown (const int& key) = 0;
	//virtual void IsMouseButtonDown(const int& button) = 0;
	//virtual void GetMousePosition() = 0;
};

extern "C"
{
	API_EXPORT IInput* CreateInputInterface(SEnvironment *env);
}