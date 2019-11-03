/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IWindowEventListener.h"

#include <functional>

typedef void(*WindowProcAddr)(void);

class IWindow
{
public:
	typedef std::function<void(const SWindowEvent&)> TEventCallbackFn;

	virtual ~IWindow() {}

	virtual void openWindow(const int& height, const int& width, TEventCallbackFn callbackFn) = 0;
	virtual WindowProcAddr getWindowProcAddress() = 0;
	virtual int getWindowId() = 0;
	virtual void closeWindow() = 0;
	virtual void onUpdate() = 0;
};