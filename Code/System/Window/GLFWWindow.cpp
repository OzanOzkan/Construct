#include "GLFWWindow.h"

#include <iostream>

/////////////////////////////////////////////////
void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	CGLFWWindow* pWindow = reinterpret_cast<CGLFWWindow*>(glfwGetWindowUserPointer(window));
	pWindow->onWindowEvent(key, action, -1, -1);
}

/////////////////////////////////////////////////
void MouseInputCallback(GLFWwindow* window, int button, int action, int mods)
{
	CGLFWWindow* pWindow = reinterpret_cast<CGLFWWindow*>(glfwGetWindowUserPointer(window));
	pWindow->onWindowEvent(button, action, -1, -1);
}

/////////////////////////////////////////////////
void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	CGLFWWindow* pWindow = reinterpret_cast<CGLFWWindow*>(glfwGetWindowUserPointer(window));
	pWindow->onWindowEvent(-1, -1, xpos, ypos);
}

/////////////////////////////////////////////////
void CGLFWWindow::onWindowEvent(const int& key, const int& action, const double& xpos, const double& ypos)
{
	SWindowEvent windowEvent;
	windowEvent.event_type = EWindowEventType::eWE_KEY_PRESSED;

	m_callbackFn(windowEvent);
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
}
