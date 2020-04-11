#pragma once

class ILevel
{
public:
	virtual ~ILevel() {}

	virtual void loadLevel() = 0;
};