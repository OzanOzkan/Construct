#pragma once

class ILevel
{
public:
	virtual void loadLevel() = 0;
	virtual void onUpdate() = 0;
};