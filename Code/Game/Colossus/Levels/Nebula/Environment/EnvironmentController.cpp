#include "EnvironmentController.h"

#include "EnvironmentObject.h"
#include "../EnemyShip.h"

#include <random>

/////////////////////////////////////////////////
CEnvironmentController::CEnvironmentController()
	: m_pScrollingBgComponent(nullptr)
	, m_resW(0)
	, m_resH(0)
	, m_enemySpawnTime(1.0f)
	, m_envObjectSpawnTime(10.f)
	, m_previousEnemySpawnTime(0.f)
	, m_previousEnvObjectSpawnTime(0.f)
{
}

/////////////////////////////////////////////////
void CEnvironmentController::Init()
{
	GetSystem()->GetRenderer()->getResolution(m_resW, m_resH);

	// Scrolling background
	ConfigureBackground();
}

/////////////////////////////////////////////////
unsigned int CEnvironmentController::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void CEnvironmentController::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
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
	m_pScrollingBgComponent->setFile("Sprites/background/NebulaRed.png");
	m_pScrollingBgComponent->setLayerId(-1);

	SSpriteParams::SSpriteScrollParams scrollParams;
	scrollParams.scrollSpeed = 100.f;
	scrollParams.scrollDirection = SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection::eSPD_DOWN;
	m_pScrollingBgComponent->setScrollParams(scrollParams);

	m_pScrollingBgComponent->updateComponent();
}

/////////////////////////////////////////////////
void CEnvironmentController::ProcessUpdateEvent()
{
	float currentTime = GetSystem()->GetTime()->GetSystemTime();

	if (currentTime - m_previousEnemySpawnTime > m_enemySpawnTime) {
		int randPos = rand() % (m_resW - 0 + 1);

		SEntitySpawnParams enemySpawnParams;
		enemySpawnParams.entityName = "EnemyShip";
		enemySpawnParams.position = Vector2(randPos, -100.f);

		GetSystem()->GetEntitySystem()->spawnEntity(enemySpawnParams)->addEntityComponent<CEnemyShip>();

		m_previousEnemySpawnTime = currentTime;
	}

	if (currentTime - m_previousEnvObjectSpawnTime > m_envObjectSpawnTime) {
		SEntitySpawnParams environmentObjectSpawnParams;
		environmentObjectSpawnParams.entityName = "EnvironmentObject";
		environmentObjectSpawnParams.position = Vector2(m_resW / 2, -200.f);

		GetSystem()->GetEntitySystem()->spawnEntity(environmentObjectSpawnParams)
			->addEntityComponent<CEnvironmentObject>();

		m_previousEnvObjectSpawnTime = currentTime;
	}
}