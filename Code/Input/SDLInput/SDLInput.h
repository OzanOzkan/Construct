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
	void onPreUpdate() override {}
	void onUpdate() override;
	void onPostUpdate() override {}
	bool IsKeyPressed(const EKey& key) override;
	Vector2 GetMousePosition() override;
	STouchEventList GetTouchEvents() override;
	// ~IInput

private:
	ISystem * GetSystem() noexcept { return m_pSystem; }

private:
	ISystem * m_pSystem;
	SWindowSize m_windowSize;
	int m_numTouchDevices;
};