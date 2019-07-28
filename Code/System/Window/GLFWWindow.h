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

	void closeWindow();
	void onUpdate();
	TEventCallbackFn GetCallbackFunction() { return m_callbackFn; }

private:
	GLFWwindow * m_pWindow;
	TEventCallbackFn m_callbackFn;
};