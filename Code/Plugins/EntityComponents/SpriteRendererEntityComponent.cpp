#include "SpriteRendererEntityComponent.h"

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityBasicTypes.h>
#include <Renderer/IRenderer.h>
#include <ILog.h>

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::Init()
{

}

/////////////////////////////////////////////////
unsigned int SpriteRendererEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEvent(const EEntityEvent & event)
{
	switch (event)
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		onEntityUpdate();
	}
	break;
	}
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::updateComponent()
{
	SSpriteCreateParams params;
	params.spriteFile = m_spriteFile;
	params.position = getEntity()->getPosition();
	params.width = 350;
	params.height = 500;

	m_pSprite = static_cast<ISprite*>(GetSystem()->GetRenderer()->CreateRenderObject(params));
	m_pSprite->setRenderActive(true);

}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEntityUpdate()
{
	m_pSprite->setPosition(getEntity()->getPosition());
}