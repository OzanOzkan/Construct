/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <Core.h>
#include <IInput.h>
#include <System/ISystem.h>
#include <System/IWindowEventListener.h>

class CInput : public IInput, IWindowEventListener 
{
public:
	CInput(ISystem* systemContext);

	// IModule
	void InitializeModule() override;
	void onUpdate() override;
	// ~IModule

	// IInput
	void RegisterEventListener(InputEventListener* listener) override;
	void RemoveEventListener(InputEventListener* listener) override;

	void PostInputEvent(const SInputEvent& event) override;

	//virtual void IsKeyDown(const int& key) override;
	//virtual void IsMouseButtonDown(const int& button) override;
	// ~IInput

	// IWindowEventListener
	void onWindowEvent(const SWindowEvent& event) override;
	// ~IWindowEventListener

protected:
	std::set<InputEventListener*> m_listeners;

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem;
};