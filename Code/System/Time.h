#pragma once 

#include <System/ITime.h>

class CTime : public ITime
{
public:
	CTime();

	float GetSystemTime() override;
	float GetDeltaTime() override;

	void onPreUpdate();

private:
	float m_currentTime;
	float m_previousTime;
	float m_deltaTime;
};