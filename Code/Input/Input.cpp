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
	API_EXPORT IInput* CreateInputInterface(SEnvironment *env)
	{
		std::unique_ptr<CInput> pInput = std::make_unique<CInput>(env);

		return pInput.release();
	}
}

/////////////////////////////////////////////////
CInput::CInput(SEnvironment* env)
	:m_pEnv(env)
{

}

/////////////////////////////////////////////////
CInput::~CInput()
{

}

/////////////////////////////////////////////////
void CInput::InitializeModule()
{
	m_pEnv->pSystem->registerWindowEvents(this);
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
		m_pEnv->pLog->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_KEY_RELEASED:
	{
		std::string logMsg = "CInput::onWindowEvent(): eWE_KEY_RELEASED: ";
		logMsg += std::to_string(event.scancode);
		m_pEnv->pLog->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_MOUSE_POSITION_CHANGED:
	{
		std::string logMsg = "CInput::onWindowEvent() : eWE_MOUSE_POSITION_CHANGED: ";
		auto posx = std::to_string(event.x);
		auto posy = std::to_string(event.y);
		logMsg += posx + " " + posy;

		m_pEnv->pLog->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_MOUSE_BUTTON_PRESSED:
	{
		std::string logMsg = "CInput::onWindowEvent() : eWE_MOUSE_BUTTON_PRESSED: ";
		logMsg += std::to_string(event.scancode);
		m_pEnv->pLog->Log(logMsg.c_str());
	}
	break;
	case EWindowEventType::eWE_MOUSE_BUTTON_RELEASED:
	{
		std::string logMsg = "CInput::onWindowEvent() : eWE_MOUSE_BUTTON_RELEASED: ";
		logMsg += std::to_string(event.scancode);
		m_pEnv->pLog->Log(logMsg.c_str());
	}
	break;
	default:
	{
		m_pEnv->pLog->Log("CInput::onWindowEvent(): Unhandled window event.");
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