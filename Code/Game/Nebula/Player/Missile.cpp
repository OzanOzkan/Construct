/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Missile.h"

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <ILog.h>

#include <Physics/IPhysics.h>

/////////////////////////////////////////////////
CMissile::CMissile()
	:m_pSpriteRendererComponent(nullptr)
	, m_pTestCollisionComponent(nullptr)
{
}

/////////////////////////////////////////////////
void CMissile::Init()
{
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	m_pSpriteRendererComponent->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Missile1.png");
	m_pSpriteRendererComponent->setLayerId(10);
	m_pSpriteRendererComponent->updateComponent();

	//m_pSpriteRendererComponent->setDebugDraw(true);

	m_windowSize = GetSystem()->GetWindowManager()->GetWindowSize();

	getEntity()->setTimer(1.5);

	m_pTestCollisionComponent = getEntity()->addEntityComponent<CollisionEntityComponent>();
	m_pTestCollisionComponent->SetSize(20, 20);
	m_pTestCollisionComponent->updateComponent();
}

/////////////////////////////////////////////////
unsigned int CMissile::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_TIMER_TICK | EEntityEvent::ENTITY_EVENT_COLLISION;
}

/////////////////////////////////////////////////
void CMissile::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		updateEvent();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_TIMER_TICK:
	{
		destroyMissile();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_COLLISION:
	{
		auto eventData = event.GetData<SPhysicsEventData>();
		if (eventData->pEntity2->getTag().compare("EnemyShip") == 0)
		{
			destroyMissile();
		}
	}
	break;
	}
}

/////////////////////////////////////////////////
void CMissile::updateComponent()
{
}

/////////////////////////////////////////////////
void CMissile::updateEvent()
{
	// Move the missile as an entity at each update.
	getEntity()->setPosition(getEntity()->getPosition() - Vector2(0, 30));
}

/////////////////////////////////////////////////
void CMissile::destroyMissile()
{
	GetSystem()->GetEntitySystem()->destroyEntity(m_pEntity->getID());
}
