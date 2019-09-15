#include "GLFWWindow.h"

#include <IInput.h>

#include <iostream>

/////////////////////////////////////////////////
void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	CGLFWWindow* pWindow = reinterpret_cast<CGLFWWindow*>(glfwGetWindowUserPointer(window));
	SWindowEvent event;
	
	switch (action)
	{
	case 0:
		event.event_type = EWindowEventType::eWE_KEY_RELEASED;
		break;
	case 1:
		event.event_type = EWindowEventType::eWE_KEY_PRESSED;
		break;
	}

	event.scancode = scancode;

	pWindow->GetCallbackFunction()(event);
}

/////////////////////////////////////////////////
void MouseInputCallback(GLFWwindow* window, int button, int action, int mods)
{
	CGLFWWindow* pWindow = reinterpret_cast<CGLFWWindow*>(glfwGetWindowUserPointer(window));
	SWindowEvent event;

	switch (action)
	{
	case 0:
		event.event_type = EWindowEventType::eWE_MOUSE_BUTTON_RELEASED;
		break;
	case 1:
		event.event_type = EWindowEventType::eWE_MOUSE_BUTTON_PRESSED;
		break;
	}

	event.buttoncode = button;

	pWindow->GetCallbackFunction()(event);
}

/////////////////////////////////////////////////
void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	CGLFWWindow* pWindow = reinterpret_cast<CGLFWWindow*>(glfwGetWindowUserPointer(window));
	
	SWindowEvent event;
	event.event_type = EWindowEventType::eWE_MOUSE_POSITION_CHANGED;
	event.x = xpos;
	event.y = ypos;

	pWindow->GetCallbackFunction()(event);
}

/////////////////////////////////////////////////
CGLFWWindow::CGLFWWindow(const int& height, const int& width, TEventCallbackFn callbackFn)
{
	m_callbackFn = callbackFn;

	glfwInit();

	m_pWindow = glfwCreateWindow(height, width, "ProjectO01", nullptr, nullptr);

	glfwMakeContextCurrent(m_pWindow);
	glfwSetWindowUserPointer(m_pWindow, this);
	glfwSetKeyCallback(m_pWindow, KeyboardInputCallback);
	glfwSetMouseButtonCallback(m_pWindow, MouseInputCallback);
	glfwSetCursorPosCallback(m_pWindow, MousePositionCallback);
}

/////////////////////////////////////////////////
CGLFWWindow::~CGLFWWindow()
{
	closeWindow();
}

/////////////////////////////////////////////////
void CGLFWWindow::closeWindow()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

/////////////////////////////////////////////////
void CGLFWWindow::onUpdate()
{
	///* Render here */
	//glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(m_pWindow);

	/* Poll for and process events */
	glfwPollEvents();

	if (glfwWindowShouldClose(m_pWindow))
	{
		SWindowEvent event;
		event.event_type = EWindowEventType::eWE_WINDOW_CLOSED;
		GetCallbackFunction()(event);

		closeWindow();
	}
}
