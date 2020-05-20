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
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	m_pSpriteRendererComponent->setFile("Sprites/EnemyShip.png");
	m_pSpriteRendererComponent->setSize(222, 135);
	m_pSpriteRendererComponent->setLayerId(10);
	m_pSpriteRendererComponent->updateComponent();

	m_pCollisionComponent = getEntity()->addEntityComponent<CollisionEntityComponent>();
	m_pCollisionComponent->SetSize(111, 67);
	m_pCollisionComponent->updateComponent();

	getEntity()->setTag("EnemyShip");
}

/////////////////////////////////////////////////
unsigned int CEnemyShip::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_COLLISION | EEntityEvent::ENTITY_EVENT_TIMER_TICK;
}

/////////////////////////////////////////////////
void CEnemyShip::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
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
	// Move the enemy ship down on each update.
	getEntity()->setPosition(getEntity()->getPosition() + (Vector2(0, 300.f) * GetSystem()->GetTime()->GetDeltaTime()));
}

/////////////////////////////////////////////////
void CEnemyShip::onCollisionEvent()
{
	m_Health -= 10;

	if (m_Health <= 0)
		explodeShip();
}

/////////////////////////////////////////////////
void CEnemyShip::explodeShip()
{
	getEntity()->removeEntityComponent(m_pCollisionComponent);

	m_pSpriteRendererComponent->setFile("Sprites/Explosion.png");
	m_pSpriteRendererComponent->setSize(128, 500);
	m_pSpriteRendererComponent->updateComponent();
	
	getEntity()->setTimer(0.1);
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
