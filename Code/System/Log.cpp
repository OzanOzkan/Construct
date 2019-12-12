/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Log.h"

#include "SDL.h"
#include <iostream>

void CLog::Log(const char * text)
{
	// Temporary logging.
#ifdef _WIN32
	std::cout << text << std::endl;
#else
	SDL_Log("%s", text);
#endif
}
