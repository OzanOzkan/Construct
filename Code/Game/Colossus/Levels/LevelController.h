#pragma once

#include <System/ISystem.h>
#include "ILevel.h"

#include <memory>

enum class ELevel
{
	MAIN_MENU = 0,
	NEBULA,
	ISOMETRICA
};

class CLevelController
{
public:
	static CLevelController& getInstance(ISystem* systemContext);
	void loadLevel(const ELevel& level);

private:
	CLevelController(ISystem* systemContext);

private:
	ISystem* m_pSystem;
	std::unique_ptr<ILevel> m_pCurrentLevel;
};