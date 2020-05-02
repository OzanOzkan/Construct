#include "SDLInput.h"

#include <Renderer/IRenderer.h>
#include <ILog.h>

/////////////////////////////////////////////////
CSDLInput::CSDLInput(ISystem* systemContext)
	: m_pSystem(systemContext)
	, m_numTouchDevices(-1)
{
}

/////////////////////////////////////////////////
void CSDLInput::InitializeModule() 
{
	m_windowSize = GetSystem()->GetWindowManager()->GetWindowSize();

	// Get number of available touch devices
	m_numTouchDevices = SDL_GetNumTouchDevices();
}

/////////////////////////////////////////////////
void CSDLInput::onUpdate() 
{

}

/////////////////////////////////////////////////
bool CSDLInput::IsKeyPressed(const EKey & key) 
{
	bool retValue = false;

	if (key >= EKey::eKID_MOUSE_LEFT && key <= EKey::eKID_MOUSE_RIGHT)
	{
		// Handle Mouse Input
		const int scancodeCorrection = ((uint8_t)key - 1000) + 1;
		retValue = SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(scancodeCorrection);
	}
	else
	{
		// Handle Keyboard Input
		const uint8_t* state = (uint8_t*)SDL_GetKeyboardState(nullptr);
		retValue = state[(Uint8)key] ? true : false;
	}

	return retValue;
}

/////////////////////////////////////////////////
Vector2 CSDLInput::GetMousePosition()
{
	// Calculates mouse position relative to the render resolution.

	int rawMouseX, rawMouseY;
	SDL_GetMouseState(&rawMouseX, &rawMouseY);

	int resolutionW, resolutionH;
	GetSystem()->GetRenderer()->getResolution(resolutionW, resolutionH);

	const SWindowSize windowSize = GetSystem()->GetWindowManager()->GetWindowSize();

	const float fx = float(rawMouseX) / float(windowSize.width) * float(resolutionW);
	const float fy = float(rawMouseY) / float(windowSize.height) * float(resolutionH);

	return Vector2(fx, fy);
}

/////////////////////////////////////////////////
STouchEventList CSDLInput::GetTouchEvents()
{
	STouchEventList retList;
	const SWindowSize windowSize = GetSystem()->GetWindowManager()->GetWindowSize();

	for (int deviceIndex = 0; deviceIndex < m_numTouchDevices; ++deviceIndex)
	{
		const SDL_TouchID touchId = SDL_GetTouchDevice(deviceIndex);
		const int numFingers = SDL_GetNumTouchFingers(touchId);

		for (int fingerIndex = 0; fingerIndex < numFingers; ++fingerIndex)
		{
			const SDL_Finger* finger = SDL_GetTouchFinger(touchId, fingerIndex);

			STouchEvent touchEvent;
			touchEvent.fingerId = (int)finger->id;
			touchEvent.position = Vector2(finger->x * windowSize.width, finger->y * windowSize.height);
			touchEvent.pressure = finger->pressure;

			retList.emplace_back(touchEvent);
		}
	}

	return retList;
}
