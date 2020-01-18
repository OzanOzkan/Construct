/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Missile.h"

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <ILog.h>

/////////////////////////////////////////////////
CMissile::CMissile()
	:m_pSpriteRendererComponent(nullptr)
{
}

/////////////////////////////////////////////////
void CMissile::Init()
{
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>("MissileSprite");
	m_pSpriteRendererComponent->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Missile1.png");
	m_pSpriteRendererComponent->setLayerId(10);
	m_pSpriteRendererComponent->updateComponent();

	m_windowSize = GetSystem()->GetWindowManager()->GetWindowSize();

	getEntity()->setTimer(1.5);
}

/////////////////////////////////////////////////
unsigned int CMissile::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_TIMER_TICK;
}

/////////////////////////////////////////////////
void CMissile::onEvent(const EEntityEvent & event)
{
	switch (event)
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
