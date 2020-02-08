/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "StdAfx.h"
#include "Game.h"

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>
#include <System/IFileManager.h>

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
	SEntitySpawnParams environmentControllerSpawnParams;
	environmentControllerSpawnParams.entityName = "EnvironmentControllerEntity";
	GetSystem()->GetEntitySystem()->spawnEntity(environmentControllerSpawnParams)
		->addEntityComponent<CEnvironmentController>();


	SEntitySpawnParams playerSpawnParams;
	playerSpawnParams.entityName = "PlayerEntity";
	GetSystem()->GetEntitySystem()->spawnEntity(playerSpawnParams)
		->addEntityComponent<CPlayer>();
}