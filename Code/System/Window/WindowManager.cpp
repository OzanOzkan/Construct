#include "WindowManager.h"
#include "SDLWindow.h"
#include <ILog.h>

#include <iostream>

/////////////////////////////////////////////////
CWindowManager::CWindowManager(ISystem * systemContext)
	: m_pSystem(systemContext)
	, m_width(490)
	, m_height(1000)
{
}

/////////////////////////////////////////////////
void CWindowManager::initWindow(const EWindowType& windowType, void* renderTarget)
{
	switch (windowType)
	{
	case EWindowType::eWT_SDL2:
	{
		m_activeWindow = std::make_unique<CSDLWindow>(m_pSystem);
		GetSystem()->GetLogger()->Log("CWindowManager:initWindow: Initializing SDL2 Window");
	}
	break;
	default:
	{
		// TODO
	}
	break;
	}
	
	if (m_activeWindow)
	{
		m_activeWindow.get()->openWindow(
			m_height,
			m_width,
			[this](const SWindowEvent& event) { onWindowEvent(event); },
			renderTarget
		);
	}
}

/////////////////////////////////////////////////
const int& CWindowManager::GetWindowId()
{
	return m_activeWindow->getWindowId();
}

/////////////////////////////////////////////////
const SWindowSize & CWindowManager::GetWindowSize()
{
	return m_activeWindow->getWindowSize();
}

/////////////////////////////////////////////////
void CWindowManager::setWindowSize(const int& width, const int& height)
{
	m_height = height;
	m_width = width;
	m_activeWindow->setWindowSize(m_width, m_height);
}

/////////////////////////////////////////////////
void CWindowManager::registerWindowEvents(IWindowEventListener* listener)
{
	m_eventListeners.insert(listener);
}

/////////////////////////////////////////////////
void CWindowManager::unregisterWindowEvents(IWindowEventListener* listener)
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