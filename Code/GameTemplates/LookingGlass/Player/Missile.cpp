#include "Missile.h"

#include <System/EntitySystem/IEntity.h>

#ifdef _WIN32
#define SPRITE_FILE "F:\\Development\\ProjectO01\\Assets\\Sprites\\Missile1.png"
#else
#define SPRITE_FILE "Sprites/Missile1.png"
#endif


CMissile::CMissile()
	:m_pSpriteRendererComponent(nullptr)
{
}

void CMissile::Init()
{
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>("MissileSprite");
	m_pSpriteRendererComponent->setFile(SPRITE_FILE);
	m_pSpriteRendererComponent->setSize(26, 8);
	m_pSpriteRendererComponent->updateComponent();
	m_pSpriteRendererComponent->setActive(true);
}

unsigned int CMissile::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

void CMissile::onEvent(const EEntityEvent & event)
{
	switch (event)
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		updateEvent();
	}
	break;
	}
}

void CMissile::updateComponent()
{
}

void CMissile::updateEvent()
{
	// Move the missile as an entity at each update.
	getEntity()->setPosition(getEntity()->getPosition() - Vector2(0, 10));
}
