#include "Game.h"

#include "Levels/LevelController.h"
#include <Renderer/IRenderer.h>

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntityComponent.h>

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
CGame::CGame(ISystem* systemContext) noexcept
	: m_pSystem(systemContext)
{

}

/////////////////////////////////////////////////
void CGame::InitializeModule()
{
	constexpr int width = 1080;
	constexpr int height = 2220;
	GetSystem()->GetRenderer()->setResolution(width, height);

	loadLevel();
}

/////////////////////////////////////////////////
void CGame::onUpdate()
{
	CLevelController::getInstance(m_pSystem).onUpdate();
}

/////////////////////////////////////////////////
void CGame::loadLevel()
{
	CLevelController::getInstance(m_pSystem).loadLevel(ELevel::MAIN_MENU);
}