#include "TextRendererEntityComponent.h"

#include <System/EntitySystem/IEntity.h>
#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
void TextRendererEntityComponent::Init()
{

}

/////////////////////////////////////////////////
unsigned int TextRendererEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_DESTROY;
}

/////////////////////////////////////////////////
void TextRendererEntityComponent::onEvent(const EEntityEvent & event)
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
void TextRendererEntityComponent::updateComponent()
{
	STextParams params;
	params.text = m_text;
	params.font = m_font;
	params.fontSize = m_fontSize;
	params.position = getEntity()->getPosition();

	m_pText = static_cast<IText*>(GetSystem()->GetRenderer()->CreateRenderObject(params));
	m_pText->setRenderActive(true);
}

/////////////////////////////////////////////////
void TextRendererEntityComponent::onEntityUpdateEvent()
{
	m_pText->setPosition(getEntity()->getPosition());
}

/////////////////////////////////////////////////
void TextRendererEntityComponent::onEntityDestroyEvent()
{
	GetSystem()->GetRenderer()->RemoveRenderObject(m_pText);
}