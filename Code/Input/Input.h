#pragma once

#include <IInput.h>
#include <System/ISystem.h>
#include <System/IWindowEventListener.h>

class CInput : public IInput, IWindowEventListener 
{
public:
	CInput(SEnvironment* env);
	virtual ~CInput();

	// IModule
	virtual void InitializeModule() override;
	virtual void Update() override;
	// ~IModule

	// IInput
	virtual void RegisterEventListener(InputEventListener* listener) override;
	virtual void RemoveEventListener(InputEventListener* listener) override;

	virtual void PostInputEvent(const SInputEvent& event) override;

	//virtual void IsKeyDown(const int& key) override;
	//virtual void IsMouseButtonDown(const int& button) override;
	// ~IInput

	// IWindowEventListener
	virtual void onWindowEvent(const SWindowEvent& event) override;
	// ~IWindowEventListener

protected:
	std::set<InputEventListener*> m_listeners;

private:
	SEnvironment * m_pEnv;

};