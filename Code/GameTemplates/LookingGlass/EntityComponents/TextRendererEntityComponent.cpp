#include "TextRendererEntityComponent.h"

#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
void TextRendererEntityComponent::Init()
{

}

/////////////////////////////////////////////////
unsigned int TextRendererEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void TextRendererEntityComponent::onEvent(const EEntityEvent & event)
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
void TextRendererEntityComponent::updateComponent()
{
	STextCreateParams params;
	params.text = m_text;
	params.font = m_font;
	params.fontSize = m_fontSize;
	params.posX = 5;
	params.posY = 5;
	params.width = 155;
	params.height = m_fontSize;

	m_pText = static_cast<IText*>(GetSystem()->GetRenderer()->CreateRenderObject(params));
	m_pText->setRenderActive(true);
}

/////////////////////////////////////////////////
void TextRendererEntityComponent::onEntityUpdate()
{

}