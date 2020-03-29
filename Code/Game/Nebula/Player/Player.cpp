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
	m_pSpriteRendererComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	m_pSpriteRendererComponent->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/PlayerShip.png");
	m_pSpriteRendererComponent->setLayerId(10);
	m_pSpriteRendererComponent->updateComponent();

	SWindowSize currentWindowSize = GetSystem()->GetWindowManager()->GetWindowSize();
	getEntity()->setPosition(Vector2((currentWindowSize.width / 2) - 133, currentWindowSize.height - 450));

	m_pWeapon1 = getEntity()->addEntityComponent<CWeapon>(); // Left weapon
	m_pWeapon1->setPosition(Vector2(55, 80)); // Relative to ship position

	m_pWeapon2 = getEntity()->addEntityComponent<CWeapon>();
	m_pWeapon2->setPosition(Vector2(200, 80));

	float h, w;
	m_pSpriteRendererComponent->getSize(h, w);
	m_pOnSelectionListenerEntityComponent = getEntity()->addEntityComponent<OnSelectionListenerEntityComponent>();
	m_pOnSelectionListenerEntityComponent->setSize(w, h);
	m_pOnSelectionListenerEntityComponent->subscribeOnSelection([this](const Vector2& selectionPos) { movePlayer(selectionPos); });
}

/////////////////////////////////////////////////
unsigned int CPlayer::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void CPlayer::onEvent(const SEntityEvent & event)
{

}

/////////////////////////////////////////////////
void CPlayer::updateComponent()
{
	
}

/////////////////////////////////////////////////
void CPlayer::movePlayer(const Vector2& toPosition)
{
	float h, w;
	m_pSpriteRendererComponent->getSize(h, w);

	getEntity()->setPosition(Vector2(toPosition.x - h/2, toPosition.y - w/2));
}
