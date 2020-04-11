#include "Game.h"

#include "Levels/LevelController.h"

extern "C"
{
	API_EXPORT IGame* CreateModuleInterface(ISystem* systemContext)
	{
		CGame* pGame = new CGame(systemContext);
		pGame->InitializeModule();
		return pGame;
	}
}

/////////////////////////////////////////////////
CGame::CGame(ISystem* systemContext)
	: m_pSystem(systemContext)
{

}

/////////////////////////////////////////////////
void CGame::InitializeModule()
{
	loadLevel();
}

/////////////////////////////////////////////////
void CGame::loadLevel()
{
	CLevelController::getInstance(m_pSystem).loadLevel(ELevel::MAIN_MENU);
}