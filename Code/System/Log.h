/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include <ILog.h>

class CLog : public ILog
{
public:
	void Log(const char* text) override;
};