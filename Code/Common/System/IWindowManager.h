#pragma once

#include "IWindowEventListener.h"

class IWindowManager
{
public:
	virtual ~IWindowManager() {}

	virtual void initWindow() = 0;
	virtual void setWindowSize(const int& height, const int& width) = 0;
	virtual void onUpdate() = 0;
	
	virtual void registerWindowEvents(IWindowEventListener* listener) = 0;
	virtual void unregisterWindowEvents(IWindowEventListener* listener) = 0;
	virtual void onWindowEvent(const SWindowEvent& event) = 0;
};