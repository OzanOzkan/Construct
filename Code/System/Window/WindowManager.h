/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <memory>
#include <set>
#include <functional>

#include <System/ISystem.h>
#include <System/IWindow.h>

#include "GLFWWindow.h"

enum class EWindowType
{
	eWT_NONE = 0,
	eWT_GLFW,
	eWT_SDL2
};

class CWindowManager
{
public:
	CWindowManager(SEnvironment* env);
	virtual ~CWindowManager() {};

	void initWindow(const EWindowType& windowType);
	void setWindowSize(const int& height, const int& width);
	void onUpdate();

	void registerWindowEvents(IWindowEventListener* listener);
	void unregisterWindowEvents(IWindowEventListener* listener);
	void onWindowEvent(const SWindowEvent& event);

	WindowProcAddr getWindowProcAddress();
	int getWindowId();

private:
	void notifyListeners(const SWindowEvent& event);

private:
	SEnvironment * m_pEnv;

	int m_height = 600;
	int m_width = 800;

	std::unique_ptr<IWindow> m_activeWindow = nullptr;
	std::set<IWindowEventListener*> m_eventListeners{};
};