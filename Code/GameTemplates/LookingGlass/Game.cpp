/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "StdAfx.h"
#include "Game.h"

#include "EntityComponents/SpriteRendererEntityComponent.h"

extern "C"
{
	API_EXPORT IModule* CreateGameModule(SEnvironment* env)
	{
		std::unique_ptr<CGame> pGame = std::make_unique<CGame>(env);

		return pGame.release();
	}
}

CGame::CGame(SEnvironment* env)
	: m_pEnv(env)
{

}

void CGame::InitializeModule()
{
	m_pEnv->pLog->Log("=========== Initializing Game ===========");

	SEntitySpawnParams params;
	params.entityName = "MyFirstEntity";
	IEntity* pEntity = m_pEnv->pEntitySystem->spawnEntity(params);

	//pEntity->addEntityComponent<SpriteRendererEntityComponent>("spriterenderer");

	//if (pEntity)
	//{
	//	if (SpriteRendererEntityComponent* pComponent = pEntity->getEntityComponent<SpriteRendererEntityComponent>("spriterenderer"))
	//	{
	//		pComponent->setFile("C:\\Users\\Ozann\\Documents\\GitHub\\ProjectO01\\Assets\\test.png");
	//		pComponent->updateComponent();

	//		m_pEnv->pLog->Log("pEntity->getEntityComponent(mycomponent) : TRUE");
	//	}
	//}

	SpriteRendererEntityComponent* pMarioRenderer = pEntity->addEntityComponent<SpriteRendererEntityComponent>("mario");
	pMarioRenderer->setFile("C:\\Users\\Ozann\\Documents\\GitHub\\ProjectO01\\Assets\\mario.png");
	pMarioRenderer->updateComponent();

	std::string entityDebugText = "Entity: " + pEntity->getName() + " created";
	m_pEnv->pLog->Log(entityDebugText.c_str());

	std::string debugText = pEntity->getName() + " component count: " + std::to_string(pEntity->getComponentCount());
	m_pEnv->pLog->Log(debugText.c_str());


	m_pEnv->pLog->Log("=========== Game Initialized ===========");
}
