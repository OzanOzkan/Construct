#include "Input.h"

#include <ILog.h>

#include <memory>

extern "C"
{
	API_EXPORT IInput* CreateInputInterface(SEnvironment *env)
	{
		std::unique_ptr<CInput> pInput = std::make_unique<CInput>(env);

		return pInput.release();
	}
}

CInput::CInput(SEnvironment* env)
	:m_pEnv(env)
{

}

CInput::~CInput()
{

}

void CInput::InitializeModule()
{
	m_pEnv->pSystem->GetWindowManager()->registerWindowEvents(this);
}

void CInput::Update()
{

}

void CInput::RegisterEventListener(InputEventListener* listener)
{
	m_listeners.insert(listener);
}

void CInput::RemoveEventListener(InputEventListener* listener)
{
	m_listeners.erase(listener);
}

void CInput::PostInputEvent(const SInputEvent & event)
{
	for (auto listener : m_listeners)
	{
		listener->onInputEvent(event);
	}
}

void CInput::onWindowEvent(const SWindowEvent & event)
{
	m_pEnv->pLog->Log("CInput::onWindowEvent");
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