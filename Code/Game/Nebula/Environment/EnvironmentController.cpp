/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "EnvironmentController.h"

#include "EnvironmentObject.h"
#include "../EnemyShip.h"

#include <random>

/////////////////////////////////////////////////
CEnvironmentController::CEnvironmentController()
	: m_pScrollingBgComponent(nullptr)
{
}

/////////////////////////////////////////////////
void CEnvironmentController::Init()
{
	m_windowSize = GetSystem()->GetWindowManager()->GetWindowSize();

	// Scrolling background
	ConfigureBackground();
}

/////////////////////////////////////////////////
unsigned int CEnvironmentController::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void CEnvironmentController::onEvent(const EEntityEvent & event)
{
	switch (event)
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		ProcessUpdateEvent();
	}
	break;
	}
}

/////////////////////////////////////////////////
void CEnvironmentController::updateComponent()
{

}

/////////////////////////////////////////////////
void CEnvironmentController::ConfigureBackground()
{
	SEntitySpawnParams scrollingBackgroundParams;
	scrollingBackgroundParams.entityName = "ScrollingBackgroundEntity";
	scrollingBackgroundParams.position = Vector2(0.f, 0.f);
	IEntity* pScrollingBackground = GetSystem()->GetEntitySystem()->spawnEntity(scrollingBackgroundParams);

	m_pScrollingBgComponent = pScrollingBackground->addEntityComponent<SpriteRendererEntityComponent>();
	m_pScrollingBgComponent->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/background/NebulaRed.png");
	m_pScrollingBgComponent->setLayerId(-1);

	SSpriteParams::SSpriteScrollParams scrollParams;
	scrollParams.scrollSpeed = 1.f;
	scrollParams.scrollDirection = SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection::eSPD_DOWN;
	m_pScrollingBgComponent->setScrollParams(scrollParams);

	m_pScrollingBgComponent->updateComponent();
}

/////////////////////////////////////////////////
void CEnvironmentController::ProcessUpdateEvent()
{
	static int delay = 2000;
	++delay;

	if (delay >= 2000)
	{
		SEntitySpawnParams environmentObjectSpawnParams;
		environmentObjectSpawnParams.entityName = "EnvironmentObject";
		environmentObjectSpawnParams.position = Vector2(m_windowSize.width / 2, -200.f);
		
		GetSystem()->GetEntitySystem()->spawnEntity(environmentObjectSpawnParams)
			->addEntityComponent<CEnvironmentObject>();

		delay = 0;
	}

	static int enemyDelay = 1000;
	++enemyDelay;

	if (enemyDelay >= 50)
	{
		int randPos = rand()% ((int)m_windowSize.width - 0 + 1);

		SEntitySpawnParams enemySpawnParams;
		enemySpawnParams.entityName = "EnemyShip";
		enemySpawnParams.position = Vector2(randPos, -100.f);

		GetSystem()->GetEntitySystem()->spawnEntity(enemySpawnParams)->addEntityComponent<CEnemyShip>();

		enemyDelay = 0;
	}
}