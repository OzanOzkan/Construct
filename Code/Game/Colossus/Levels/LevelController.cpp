#include "LevelController.h"

#include "MainMenu/MainMenu.h"
#include "Nebula/Nebula.h"
#include "Isometrica/Isometrica.h"
#include "Physica/Physica.h"

/////////////////////////////////////////////////
CLevelController::CLevelController(ISystem * systemContext) noexcept
	: m_pSystem(systemContext)
	, m_pCurrentLevel(nullptr)
{
}

/////////////////////////////////////////////////
CLevelController& CLevelController::getInstance(ISystem* systemContext) noexcept
{
	static CLevelController levelController (systemContext);
	return levelController;
}

/////////////////////////////////////////////////
void CLevelController::loadLevel(const ELevel & level)
{
	switch (level)
	{
	case ELevel::MAIN_MENU:
	{
		m_pCurrentLevel = std::make_unique<CMainMenu>(m_pSystem);
	}
	break;
	case ELevel::NEBULA:
	{
		m_pCurrentLevel = std::make_unique<CNebula>(m_pSystem);
	}
	break;
	case ELevel::ISOMETRICA:
	{
		m_pCurrentLevel = std::make_unique<CIsometrica>(m_pSystem);
	}
	break;
	case ELevel::PHYSICA:
	{
		m_pCurrentLevel = std::make_unique<CPhysica>(m_pSystem);
	}
	break;
	}

	m_pCurrentLevel->loadLevel();
}

/////////////////////////////////////////////////
void CLevelController::onUpdate()
{
	if (m_pCurrentLevel)
		m_pCurrentLevel->onUpdate();
}
