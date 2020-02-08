#include "SpriteRendererEntityComponent.h"

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityBasicTypes.h>
#include <Renderer/IRenderer.h>
#include <ILog.h>

/////////////////////////////////////////////////
SpriteRendererEntityComponent::SpriteRendererEntityComponent()
	: m_spriteFile("")
	, m_color()
	, m_height(-1)
	, m_width(-1)
	, m_pSprite(nullptr)
	, m_debugDraw(false)
	, m_pDebugRect(nullptr)
	, m_pDebugText(nullptr)
{
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::Init()
{

}

/////////////////////////////////////////////////
unsigned int SpriteRendererEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_DESTROY;
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEvent(const EEntityEvent & event)
{
	switch (event)
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		onEntityUpdateEvent();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_DESTROY:
	{
		onEntityDestroyEvent();
	}
	break;
	}
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::updateComponent()
{
	if(m_pSprite) GetSystem()->GetRenderer()->RemoveRenderObject(m_pSprite);

	SSpriteParams params;
	params.layerId = m_layerId;
	params.spriteFile = m_spriteFile;
	params.position = getEntity()->getPosition();
	params.width = m_width;
	params.height = m_height;
	params.scrollParams = m_scrollParams;

	m_pSprite = static_cast<ISprite*>(GetSystem()->GetRenderer()->CreateRenderObject(params));
	m_pSprite->setRenderActive(true);
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::setSize(const float & height, const float & width)
{
	if (m_pSprite)
	{
		m_pSprite->setSize(width, height);
	}
	else
	{
		m_width = width;
		m_height = height;
	}
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::getSize(float& height, float& width)
{
	if (m_pSprite)
	{
		height = m_pSprite->getHeight();
		width = m_pSprite->getWidth();
	}
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::setColor(const RGBColor& color)
{
	if (m_pSprite)
		m_pSprite->setColor(color);
	else
		m_color = color;
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::setDebugDraw(const bool & isActive)
{
	m_debugDraw = isActive;
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEntityUpdateEvent()
{
	if(m_pSprite)
		m_pSprite->setPosition(getEntity()->getPosition() + getPosition());

	if (m_debugDraw)
		DebugDraw();
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEntityDestroyEvent()
{
	if(m_pSprite) GetSystem()->GetRenderer()->RemoveRenderObject(m_pSprite);
	if (m_pDebugRect) GetSystem()->GetRenderer()->RemoveRenderObject(m_pDebugRect);
	if (m_pDebugText) GetSystem()->GetRenderer()->RemoveRenderObject(m_pDebugText);
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::DebugDraw()
{
	int layerId = 98;

	// Bounding box
	if (!m_pDebugRect)
	{
		SRectParams params;
		params.layerId = layerId;
		params.position = getEntity()->getPosition() + getPosition();
		params.height = m_pSprite->getHeight();
		params.width = m_pSprite->getWidth();

		m_pDebugRect = (IRect*)GetSystem()->GetRenderer()->CreateRenderObject(params);
		m_pDebugRect->setRenderActive(true);
	}
	else
	{
		m_pDebugRect->setPosition(getEntity()->getPosition() + getPosition());
	}

	// Text
	if (!m_pDebugText)
	{
		STextParams params;
		params.layerId = layerId;
		params.position = (getEntity()->getPosition() + getPosition()) - Vector2(0, 15);
		params.text = m_spriteFile + " ID: " + std::to_string(GetSystem()->GetRenderer()->GetTextureManager()->GetTexture(m_spriteFile)->GetId());
		params.fontSize = 15;

		m_pDebugText = (IText*)GetSystem()->GetRenderer()->CreateRenderObject(params);
		m_pDebugText->setRenderActive(true);
	}
	else
	{
		m_pDebugText->setPosition((getEntity()->getPosition() + getPosition()) - Vector2(0, 15));
	}
}