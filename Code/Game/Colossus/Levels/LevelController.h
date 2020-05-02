#pragma once

#include <System/ISystem.h>
#include "ILevel.h"

#include <memory>

enum class ELevel
{
	MAIN_MENU = 0,
	NEBULA,
	ISOMETRICA,
	PHYSICA
};

class CLevelController
{
public:
	static CLevelController& getInstance(ISystem* systemContext) noexcept;
	void loadLevel(const ELevel& level);
	void onUpdate();

private:
	CLevelController(ISystem* systemContext) noexcept;

private:
	ISystem* m_pSystem;
	std::unique_ptr<ILevel> m_pCurrentLevel;
};