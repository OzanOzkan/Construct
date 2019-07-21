#pragma once

#include <GLFW/glfw3.h>

#include <set>
#include <functional>

class IWindowEventListener 
{
public:
	virtual void onWindowEvent(const int& key, const int& action) = 0;
};

class CWindow
{
public:
	CWindow();
	virtual ~CWindow();

	void initWindow();
	void closeWindow();
	void onUpdate();
	void onWindowEvent(const int& key, const int& action);
	
	void addEventListener(IWindowEventListener* listener);
	void removeEventListener(IWindowEventListener* listener);

private:
	int m_height = 800;
	int m_width = 600;
	GLFWwindow* m_pWindow;
	std::set<IWindowEventListener*> m_eventListeners;
};