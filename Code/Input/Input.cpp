/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Input.h"

#include <ILog.h>
#include <Renderer/IRenderer.h>

#include <string>
#include <memory>

extern "C"
{
	API_EXPORT IInput* CreateInputInterface(ISystem* systemContext)
	{
		IInput* pInput = new CInput(systemContext);

		return pInput;
	}
}

/////////////////////////////////////////////////
CInput::CInput(ISystem* systemContext)
	:m_pSystem(systemContext)
{

}

/////////////////////////////////////////////////
void CInput::InitializeModule()
{
	GetSystem()->registerWindowEvents(this);
}

/////////////////////////////////////////////////
void CInput::onUpdate()
{

}

/////////////////////////////////////////////////
void CInput::RegisterEventListener(InputEventListener* listener)
{
	m_listeners.insert(listener);
}

/////////////////////////////////////////////////
void CInput::RemoveEventListener(InputEventListener* listener)
{
	m_listeners.erase(listener);
}

/////////////////////////////////////////////////
void CInput::PostInputEvent(const SInputEvent & event)
{
	for (auto listener : m_listeners)
	{
		listener->onInputEvent(event);
	}
}

/////////////////////////////////////////////////
void CInput::onWindowEvent(const SWindowEvent & event)
{
	switch (event.event_type)
	{
	case EWindowEventType::eWE_KEY_PRESSED:
	{
		std::string logMsg = "CInput::onWindowEvent(): eWE_KEY_PRESSED: ";
		logMsg += std::to_string(event.scancode);
		GetSystem()->GetLogger()->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_KEY_RELEASED:
	{
		std::string logMsg = "CInput::onWindowEvent(): eWE_KEY_RELEASED: ";
		logMsg += std::to_string(event.scancode);
		GetSystem()->GetLogger()->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_MOUSE_POSITION_CHANGED:
	{
		std::string logMsg = "CInput::onWindowEvent() : eWE_MOUSE_POSITION_CHANGED: ";
		auto posx = std::to_string(event.x);
		auto posy = std::to_string(event.y);
		logMsg += posx + " " + posy;

		GetSystem()->GetLogger()->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_MOUSE_BUTTON_PRESSED:
	{
		std::string logMsg = "CInput::onWindowEvent() : eWE_MOUSE_BUTTON_PRESSED: ";
		logMsg += std::to_string(event.scancode);
		GetSystem()->GetLogger()->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_MOUSE_BUTTON_RELEASED:
	{
		std::string logMsg = "CInput::onWindowEvent() : eWE_MOUSE_BUTTON_RELEASED: ";
		logMsg += std::to_string(event.scancode);
		GetSystem()->GetLogger()->Log(logMsg.c_str());
	}
	break;
	default:
	{
		GetSystem()->GetLogger()->Log("CInput::onWindowEvent(): Unhandled window event.");
	}
	break;
	}
}

//void CInput::IsKeyDown(const int& key)
//{
//
//}
//
//void CInput::IsMouseButtonDown(const int& button)
//{
//
//}