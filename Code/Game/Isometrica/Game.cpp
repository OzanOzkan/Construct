/* Copyright (C) 2020 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Game.h"

#include <System/ISystem.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>

#include "Player/Player.h"
#include "Environment/EnvironmentController.h"

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
	SEntitySpawnParams params;

	params.entityName = "Player";
	GetSystem()->GetEntitySystem()->spawnEntity(params)->addEntityComponent<CPlayer>();

	params.entityName = "EnvironmentController";
	GetSystem()->GetEntitySystem()->spawnEntity(params)->addEntityComponent<CEnvironmentController>();
}