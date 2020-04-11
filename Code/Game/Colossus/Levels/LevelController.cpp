#include "LevelController.h"

#include "MainMenu/MainMenu.h"
#include "Nebula/Nebula.h"
#include "Isometrica/Isometrica.h"

/////////////////////////////////////////////////
CLevelController::CLevelController(ISystem * systemContext)
	: m_pSystem(systemContext)
	, m_pCurrentLevel(nullptr)
{
}

/////////////////////////////////////////////////
CLevelController& CLevelController::getInstance(ISystem* systemContext)
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
	}

	m_pCurrentLevel->loadLevel();
}
