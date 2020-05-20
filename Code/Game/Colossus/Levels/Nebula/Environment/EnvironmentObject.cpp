#include "EnvironmentObject.h"

#include <ILog.h>

/////////////////////////////////////////////////
CEnvironmentObject::CEnvironmentObject()
	: m_pSpriteComponent(nullptr)
{
}

/////////////////////////////////////////////////
void CEnvironmentObject::Init()
{
	getEntity()->setTimer(150.f);

	m_pSpriteComponent = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	m_pSpriteComponent->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/background/Planets/Earthlike1.png");
	m_pSpriteComponent->setLayerId(9);
	m_pSpriteComponent->setSize(200, 200);
	m_pSpriteComponent->updateComponent();
}

/////////////////////////////////////////////////
unsigned int CEnvironmentObject::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_TIMER_TICK;
}

/////////////////////////////////////////////////
void CEnvironmentObject::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		getEntity()->setPosition(getEntity()->getPosition() + (Vector2(0, 100.f) * GetSystem()->GetTime()->GetDeltaTime()));
	}
	break;
	case EEntityEvent::ENTITY_EVENT_TIMER_TICK:
	{
		GetSystem()->GetEntitySystem()->destroyEntity(getEntity()->getID());
	}
	break;
	}
}

/////////////////////////////////////////////////
void CEnvironmentObject::updateComponent()
{
}
