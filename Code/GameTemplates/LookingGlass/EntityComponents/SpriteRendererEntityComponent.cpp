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
	params.posX = 10;
	params.posY = 10;
	params.width = 70;
	params.height = 100;

	m_pSprite = static_cast<ISprite*>(GetSystem()->GetRenderer()->CreateRenderObject(params));
	m_pSprite->setRenderActive(true);

}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEntityUpdate()
{
	m_pSprite->setPosition(m_pSprite->getPosX() + 0.01f, m_pSprite->getPosY() + 0.01f);
}