/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "StdAfx.h"
#include "Game.h"

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>

#include "Player/Player.h"

extern "C"
{
	API_EXPORT IModule* CreateGameModule(ISystem* systemContext)
	{
		CGame* pGame = new CGame(systemContext);

		return pGame;
	}
}

CGame::CGame(ISystem* systemContext)
	: m_pSystem(systemContext)
{

}

void CGame::InitializeModule()
{
	GetSystem()->GetLogger()->Log("=========== Initializing Game ===========");

	SEntitySpawnParams params;
	params.entityName = "PlayerEntity";
	IEntity* pEntity = GetSystem()->GetEntitySystem()->spawnEntity(params);
	pEntity->addEntityComponent<CPlayer>("Player");

	std::string entityDebugText = "Entity: " + pEntity->getName() + " created";
	GetSystem()->GetLogger()->Log(entityDebugText.c_str());

	std::string debugText = pEntity->getName() + " component count: " + std::to_string(pEntity->getComponentCount());
	GetSystem()->GetLogger()->Log(debugText.c_str());


	GetSystem()->GetLogger()->Log("=========== Game Initialized ===========");
}
