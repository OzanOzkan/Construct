#include "Game.h"

#include <Renderer/IRenderer.h>
#include <System/LevelSystem/ILevelSystem.h>

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

	GetSystem()->GetLevelSystem()->loadLevel("MainMenu");
}

/////////////////////////////////////////////////
void CGame::onUpdate()
{

}