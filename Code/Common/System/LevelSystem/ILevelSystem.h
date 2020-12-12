#pragma once

#include <string>

class ILevelSystem
{
public:
	virtual ~ILevelSystem(){}

	virtual void loadLevel(const std::string& levelName) = 0;
	virtual void unloadLevel() = 0;
	virtual void resetLevel() = 0;
	virtual std::string getCurrentLevelName() = 0;
};