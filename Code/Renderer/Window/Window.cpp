#include "Window.h"

CWindow::~CWindow()
{

}

void CWindow::initWindow()
{
	glfwInit();

	m_pWindow = glfwCreateWindow(m_height, m_width, "ProjectO01", nullptr, nullptr);

	glfwMakeContextCurrent(m_pWindow);
}

void CWindow::closeWindow()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

void CWindow::onUpdate()
{
	///* Render here */
	//glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(m_pWindow);

	/* Poll for and process events */
	glfwPollEvents();
}
