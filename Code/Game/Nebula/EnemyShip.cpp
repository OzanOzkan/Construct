#include "EnemyShip.h"

#include <System/ISystem.h>
#include <System/EntitySystem/IEntitySystem.h>

/////////////////////////////////////////////////
CEnemyShip::CEnemyShip()
	: m_Health(100)
	, m_pSpriteRendererComponent(nullptr)
	, m_pCollisionComponent(nullptr)
{
}

/////////////////////////////////////////////////
void CEnemyShip::Init()
{
	// Initialize components.
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>("ShipSprite");
	m_pSpriteRendererComponent->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/EnemyShip.png");
	m_pSpriteRendererComponent->setSize(222, 135);
	m_pSpriteRendererComponent->setLayerId(10);
	m_pSpriteRendererComponent->updateComponent();

	m_pCollisionComponent = getEntity()->addEntityComponent<CollisionEntityComponent>("CollisionComponent");
	m_pCollisionComponent->SetSize(111, 67);
	m_pCollisionComponent->updateComponent();

	getEntity()->setTimer(150.f);
}

/////////////////////////////////////////////////
unsigned int CEnemyShip::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_COLLISION | EEntityEvent::ENTITY_EVENT_TIMER_TICK;
}

/////////////////////////////////////////////////
void CEnemyShip::onEvent(const EEntityEvent & event)
{
	switch (event)
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		onUpdateEvent();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_COLLISION:
	{
		onCollisionEvent();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_TIMER_TICK:
	{
		destroyShip();
	}
	break;
	}
}

/////////////////////////////////////////////////
void CEnemyShip::onUpdateEvent()
{
	if (m_Health <= 0)
		destroyShip();

	// Move the enemy ship down on each update.
	getEntity()->setPosition(getEntity()->getPosition() - Vector2(0, -2));
}

/////////////////////////////////////////////////
void CEnemyShip::onCollisionEvent()
{
	m_Health -= 10;
}

/////////////////////////////////////////////////
void CEnemyShip::destroyShip()
{
	GetSystem()->GetEntitySystem()->destroyEntity(m_pEntity->getID());
}

/////////////////////////////////////////////////
void CEnemyShip::updateComponent()
{
}
