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
	float m_deltaTime;
};