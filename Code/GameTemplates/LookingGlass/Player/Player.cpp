#include "Player.h"

#include <System/EntitySystem/IEntity.h>

#ifdef _WIN32
#define SPRITE_FILE "F:\\Development\\ProjectO01\\Assets\\Sprites\\PlayerShip.png"
#else
#define SPRITE_FILE "Sprites/PlayerShip.png"
#endif

/////////////////////////////////////////////////
CPlayer::CPlayer()
	: m_pSpriteRendererComponent(nullptr)
{

}

/////////////////////////////////////////////////
void CPlayer::Init()
{
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>("PlayerSprite");
	m_pSpriteRendererComponent->setFile(SPRITE_FILE);
	m_pSpriteRendererComponent->updateComponent();
	m_pSpriteRendererComponent->setActive(true);

	getEntity()->setPosition(Vector2(300, 300));
}

/////////////////////////////////////////////////
unsigned int CPlayer::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void CPlayer::onEvent(const EEntityEvent & event)
{
	
}

/////////////////////////////////////////////////
void CPlayer::updateComponent()
{

}
