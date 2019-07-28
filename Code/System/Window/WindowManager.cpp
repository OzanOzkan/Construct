#include "WindowManager.h"

#include "GLFWWindow.h"

#include <iostream>

/////////////////////////////////////////////////
void CWindowManager::setSize(const int& height, const int& width)
{
	m_height = height;
	m_width = width;
}

/////////////////////////////////////////////////
void CWindowManager::initWindow()
{
	m_activeWindow = std::make_unique<CGLFWWindow>(
		m_height, 
		m_width, 
		[this](const SWindowEvent& event) { 
			onWindowEvent(event);
		}
	);
}

/////////////////////////////////////////////////
void CWindowManager::addEventListener(IWindowEventListener* listener)
{
	m_eventListeners.insert(listener);
}

/////////////////////////////////////////////////
void CWindowManager::removeEventListener(IWindowEventListener* listener)
{
	m_eventListeners.erase(listener);
}

/////////////////////////////////////////////////
void CWindowManager::onUpdate()
{
	if (m_activeWindow)
		m_activeWindow->onUpdate();
}

/////////////////////////////////////////////////
void CWindowManager::onWindowEvent(const SWindowEvent& event)
{
	notifyListeners(event);
}

/////////////////////////////////////////////////
void CWindowManager::notifyListeners(const SWindowEvent& event)
{
	for (IWindowEventListener* listener : m_eventListeners)
	{
		listener->onWindowEvent(event);
	}
}