/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/ISystem.h>
#include <System/IWindow.h>
#include <System/IWindowEventListener.h>

#include <GLFW/glfw3.h>

class CGLFWWindow : public IWindow
{
public:
	CGLFWWindow(ISystem* systemContext);
	virtual ~CGLFWWindow();

	virtual void openWindow(const int& height, const int& width, TEventCallbackFn callbackFn) override;
	virtual WindowProcAddr getWindowProcAddress() override { return (WindowProcAddr)glfwGetProcAddress; }
	virtual int getWindowId() override { return -1; }
	virtual void closeWindow() override;
	virtual void onUpdate() override;
	TEventCallbackFn GetCallbackFunction() { return m_callbackFn; }

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
	GLFWwindow * m_pWindow = nullptr;
	TEventCallbackFn m_callbackFn;
};