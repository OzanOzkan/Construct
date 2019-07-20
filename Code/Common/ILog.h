#pragma once

class ILog
{
public:
	virtual ~ILog() {}

	virtual void Log(const char* text) = 0;
};