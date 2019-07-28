#pragma once

#include <System/IWindowEventListener.h>

#include <GLFW/glfw3.h>

#include <functional>

typedef std::function<void(const SWindowEvent&)> TEventCallbackFn;

class CGLFWWindow
{
public:
	CGLFWWindow(const int& height, const int& width, TEventCallbackFn callbackFn);
	virtual ~CGLFWWindow();

	void onWindowEvent(const int& key, const int& action, const double& xpos, const double& ypos);
	void closeWindow();
	void onUpdate();

private:
	GLFWwindow * m_pWindow;
	TEventCallbackFn m_callbackFn;
};