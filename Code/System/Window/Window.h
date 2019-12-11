/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/ISystem.h>
#include <System/IWindowEventListener.h>

#include <functional>

class CWindow
{
public:
	CWindow(ISystem* systemContext);
	virtual ~CWindow() {}

	typedef std::function<void(const SWindowEvent&)> TEventCallbackFn;

	virtual void openWindow(const int& height, const int& width, TEventCallbackFn callbackFn) = 0;
	virtual int getWindowId() = 0;
	virtual void closeWindow() = 0;
	virtual void onUpdate() = 0;
	virtual int getTicks() = 0;
	
	const SWindowSize& getWindowSize();
	TEventCallbackFn GetCallbackFunction() { return m_callbackFn; }

protected:
	ISystem * GetSystem() { return m_pSystem; }

protected:
	ISystem * m_pSystem;
	TEventCallbackFn m_callbackFn;
	bool m_quit;

	int m_height;
	int m_width;
};