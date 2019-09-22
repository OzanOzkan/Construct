#include "GLFWWindow.h"

#include <IInput.h>
#include <ILog.h>

#include <iostream>

/////////////////////////////////////////////////
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
} 

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
CGLFWWindow::CGLFWWindow(SEnvironment * env)
	: m_pEnv(env)
{
}

/////////////////////////////////////////////////
CGLFWWindow::~CGLFWWindow()
{
	closeWindow();
}

/////////////////////////////////////////////////
void CGLFWWindow::openWindow(const int & height, const int & width, TEventCallbackFn callbackFn)
{
	m_callbackFn = callbackFn;

	glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(width, height, "ProjectO01", nullptr, nullptr);
	glfwMakeContextCurrent(m_pWindow);
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(m_pWindow, this);
	glfwSetKeyCallback(m_pWindow, KeyboardInputCallback);
	glfwSetMouseButtonCallback(m_pWindow, MouseInputCallback);
	glfwSetCursorPosCallback(m_pWindow, MousePositionCallback);
	glfwSetFramebufferSizeCallback(m_pWindow, FramebufferSizeCallback);
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
	/* Poll for and process events */
	glfwPollEvents();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_pWindow);

	if (glfwWindowShouldClose(m_pWindow))
	{
		SWindowEvent event;
		event.event_type = EWindowEventType::eWE_WINDOW_CLOSED;
		GetCallbackFunction()(event);

		closeWindow();
	}
}
