#pragma once

#include <GLFW/glfw3.h>

class CWindow
{
public:
	virtual ~CWindow();

	void initWindow();
	void closeWindow();
	void onUpdate();

private:
	int m_height = 800;
	int m_width = 600;
	GLFWwindow* m_pWindow;
};