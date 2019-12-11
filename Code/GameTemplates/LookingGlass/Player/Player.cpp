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
	, m_pWeapon1(nullptr)
	, m_pWeapon2(nullptr)
{

}

/////////////////////////////////////////////////
void CPlayer::Init()
{
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>("PlayerSprite");
	m_pSpriteRendererComponent->setFile(SPRITE_FILE);
	m_pSpriteRendererComponent->setSize(259, 266); // 500, 350
	m_pSpriteRendererComponent->updateComponent();
	m_pSpriteRendererComponent->setActive(true);

	SWindowSize currentWindowSize = GetSystem()->GetWindowManager()->GetWindowSize();
	getEntity()->setPosition(Vector2((currentWindowSize.width / 2) - 133, currentWindowSize.height - 250));

	m_pWeapon1 = getEntity()->addEntityComponent<CWeapon>("Weapon1"); // Left weapon
	m_pWeapon1->setPosition(Vector2(55, 80)); // Relative to ship position

	m_pWeapon2 = getEntity()->addEntityComponent<CWeapon>("Weapon2");
	m_pWeapon2->setPosition(Vector2(200, 80));
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
