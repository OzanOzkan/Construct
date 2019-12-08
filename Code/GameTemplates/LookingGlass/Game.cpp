/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "StdAfx.h"
#include "Game.h"

#include "EntityComponents/SpriteRendererEntityComponent.h"
#include "EntityComponents/TextRendererEntityComponent.h"

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
	params.entityName = "MyFirstEntity";
	IEntity* pEntity = GetSystem()->GetEntitySystem()->spawnEntity(params);

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
#ifdef _WIN32
	pMarioRenderer->setFile("F:\\Development\\ProjectO01\\Assets\\mario.png");
#else
	pMarioRenderer->setFile("mario.png");
#endif
	pMarioRenderer->updateComponent();

	//TextRendererEntityComponent* pTextRenderer = pEntity->addEntityComponent<TextRendererEntityComponent>("myText");
	//pTextRenderer->setText("Test 123 Ozan");
	//pTextRenderer->setFont("C:\\Users\\Ozann\\Documents\\GitHub\\ProjectO01\\Assets\\Fonts\\ARIAL.TTF");
	//pTextRenderer->setFontSize(24);
	//pTextRenderer->updateComponent();

	std::string entityDebugText = "Entity: " + pEntity->getName() + " created";
	GetSystem()->GetLogger()->Log(entityDebugText.c_str());

	std::string debugText = pEntity->getName() + " component count: " + std::to_string(pEntity->getComponentCount());
	GetSystem()->GetLogger()->Log(debugText.c_str());


	GetSystem()->GetLogger()->Log("=========== Game Initialized ===========");
}
