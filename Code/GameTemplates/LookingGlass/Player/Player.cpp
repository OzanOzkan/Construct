/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Player.h"

#include <System/EntitySystem/IEntity.h>
#include <IInput.h>
#include <ILog.h>

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
	m_pSpriteRendererComponent->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/PlayerShip.png");
	m_pSpriteRendererComponent->updateComponent();
	m_pSpriteRendererComponent->setActive(true);

	SWindowSize currentWindowSize = GetSystem()->GetWindowManager()->GetWindowSize();
	getEntity()->setPosition(Vector2((currentWindowSize.width / 2) - 133, currentWindowSize.height - 450));

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
	// Control spaceship with touch input.
	STouchEventList touchEvents = GetSystem()->GetInput()->GetTouchEvents();
	if (!touchEvents.empty())
	{
		STouchEvent touchEvent = touchEvents.front();
		getEntity()->setPosition(Vector2(touchEvent.position.x - 130, touchEvent.position.y - 400));
	}
}

/////////////////////////////////////////////////
void CPlayer::updateComponent()
{
	
}
