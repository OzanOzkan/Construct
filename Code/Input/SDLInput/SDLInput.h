/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <IInput.h>
#include <SDL.h>

#include <System/IWindowManager.h>

class CSDLInput final : public IInput
{
public:
	CSDLInput(ISystem* systemContext);

	// IInput
	void InitializeModule() override;
	void onUpdate() override;
	const bool& IsKeyPressed(const EKey& key) override;
	Vector2 GetMousePosition() override;
	STouchEventList GetTouchEvents() override;
	// ~IInput

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem;
	SWindowSize m_windowSize;
	int m_numTouchDevices;
};