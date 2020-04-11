/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "SDLInput.h"

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
const bool & CSDLInput::IsKeyPressed(const EKey & key)
{
	bool retValue = false;

	if (key >= EKey::eKID_MOUSE_LEFT && key <= EKey::eKID_MOUSE_RIGHT)
	{
		// Handle Mouse Input
		int scancodeCorrection = ((uint8_t)key - 1000) + 1;
		retValue = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(scancodeCorrection);
	}
	else
	{
		// Handle Keyboard Input
		uint8_t* state = (uint8_t*)SDL_GetKeyboardState(NULL);
		retValue = state[(Uint8)key] ? true : false;
	}

	return retValue;
}

/////////////////////////////////////////////////
Vector2 CSDLInput::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	return Vector2(x, y);
}

/////////////////////////////////////////////////
STouchEventList CSDLInput::GetTouchEvents()
{
	STouchEventList retList;

	for (int deviceIndex = 0; deviceIndex < m_numTouchDevices; ++deviceIndex)
	{
		SDL_TouchID touchId = SDL_GetTouchDevice(deviceIndex);
		int numFingers = SDL_GetNumTouchFingers(touchId);

		for (int fingerIndex = 0; fingerIndex < numFingers; ++fingerIndex)
		{
			SDL_Finger* finger = SDL_GetTouchFinger(touchId, fingerIndex);

			STouchEvent touchEvent;
			touchEvent.fingerId = finger->id;
			touchEvent.position = Vector2(finger->x * m_windowSize.width, finger->y * m_windowSize.height);
			touchEvent.pressure = finger->pressure;

			retList.emplace_back(touchEvent);
		}
	}

	return retList;
}
