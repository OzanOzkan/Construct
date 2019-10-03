/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Log.h"

#include <iostream>

void CLog::Log(const char * text)
{
	std::cout << text << std::endl;
}
