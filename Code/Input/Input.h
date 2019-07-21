#pragma once

#include <ISystem.h>
#include <IInput.h>

class CInput : public IInput
{
public:
	CInput(SEnvironment* env);
	virtual ~CInput();

	// IModule
	virtual void InitializeModule() override;
	virtual void Update() override;
	// ~IModule

	// IInput
	virtual void IsKeyPressed() override;
	// ~IInput

private:
	SEnvironment * m_pEnv;
};