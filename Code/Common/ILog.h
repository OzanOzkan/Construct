/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

class ILog
{
public:
	virtual ~ILog() {}

	virtual void Log(const char* text) = 0;
};