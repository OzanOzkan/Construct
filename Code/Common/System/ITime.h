#pragma once

class ITime
{
public:
	virtual ~ITime() {}

	virtual float GetSystemTime() = 0;
	virtual float GetDeltaTime() = 0;
};