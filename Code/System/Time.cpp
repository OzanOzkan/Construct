#include "Time.h"

#include <SDL.h>

/////////////////////////////////////////////////
CTime::CTime()
	: m_deltaTime(0.f)
{
}

/////////////////////////////////////////////////
float CTime::GetSystemTime()
{
	// Removed due to insufficient implementation of chrono.
	/*return std::chrono::duration_cast<std::chrono::duration<float>>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();*/
	
	// TODO: Create platform specific implementation.
	return SDL_GetTicks() / 1000.0f; // uint32_t milliseconds to float milliseconds.
}

/////////////////////////////////////////////////
float CTime::GetDeltaTime()
{
	return m_deltaTime;
}

/////////////////////////////////////////////////
void CTime::onPreUpdate()
{
	float currentTime = GetSystemTime();
	static float previousTime = 0.f;

	m_deltaTime = currentTime - previousTime;
	previousTime = currentTime;
}
