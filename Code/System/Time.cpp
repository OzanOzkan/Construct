#include "Time.h"

#include <chrono>

/////////////////////////////////////////////////
CTime::CTime()
	: m_currentTime(0.f)
	, m_previousTime(0.f)
	, m_deltaTime(0.f)
{
}

/////////////////////////////////////////////////
float CTime::GetSystemTime()
{
	return std::chrono::duration_cast<std::chrono::duration<float>>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

/////////////////////////////////////////////////
float CTime::GetDeltaTime()
{
	return m_deltaTime;
}

/////////////////////////////////////////////////
void CTime::onPreUpdate()
{
	m_currentTime = GetSystemTime();
	m_deltaTime = m_currentTime - m_previousTime;
	m_previousTime = m_currentTime - 00000.0003;
}
