#include "Window.h"
#include <ILog.h>

/////////////////////////////////////////////////
void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	CWindow* pWindow = reinterpret_cast<CWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		pWindow->onWindowEvent(key, action);
	}
}

/////////////////////////////////////////////////
CWindow::CWindow()
{

}

/////////////////////////////////////////////////
CWindow::~CWindow()
{
	
}

/////////////////////////////////////////////////
void CWindow::initWindow()
{
	glfwInit();

	m_pWindow = glfwCreateWindow(m_height, m_width, "ProjectO01", nullptr, nullptr);

	glfwMakeContextCurrent(m_pWindow);
	glfwSetWindowUserPointer(m_pWindow, this);
	glfwSetKeyCallback(m_pWindow, KeyboardInputCallback);
}

/////////////////////////////////////////////////
void CWindow::closeWindow()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

/////////////////////////////////////////////////
void CWindow::onUpdate()
{
	///* Render here */
	//glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(m_pWindow);

	/* Poll for and process events */
	glfwPollEvents();
}

/////////////////////////////////////////////////
void CWindow::onWindowEvent(const int& key, const int& action)
{
	for (IWindowEventListener* listener : m_eventListeners)
	{
		listener->onWindowEvent(key, action);
	}
}

/////////////////////////////////////////////////
void CWindow::addEventListener(IWindowEventListener* listener)
{
	m_eventListeners.insert(listener);
}

/////////////////////////////////////////////////
void CWindow::removeEventListener(IWindowEventListener* listener)
{
	m_eventListeners.erase(listener);
}
