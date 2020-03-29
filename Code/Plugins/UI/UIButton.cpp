#include "UIButton.h"

#include <ILog.h>
#include <System/EntitySystem/IEntity.h>
#include <Renderer/IRenderer.h>

#include <algorithm>

/////////////////////////////////////////////////
UIButton::UIButton()
	: m_pBackgroundRenderer(nullptr)
	, m_pTextRenderer(nullptr)
	, m_pOnClickListener(nullptr)
{
}

/////////////////////////////////////////////////
void UIButton::Init()
{
	m_pBackgroundRenderer = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	m_pBackgroundRenderer->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Default/UI/buttonbg.png");
	m_pBackgroundRenderer->setLayerId(80);
	m_pBackgroundRenderer->updateComponent();

	m_pTextRenderer = getEntity()->addEntityComponent<TextRendererEntityComponent>();
	m_pTextRenderer->setFontSize(20);
	m_pTextRenderer->setText("Button");
	m_pTextRenderer->setLayerId(81);
	m_pTextRenderer->setPosition(Vector2(20, 5));
	m_pTextRenderer->updateComponent();


	float h, w;
	m_pBackgroundRenderer->getSize(h, w);

	m_pOnClickListener = getEntity()->addEntityComponent<OnSelectionListenerEntityComponent>();
	m_pOnClickListener->setSize(w, h);
	m_pOnClickListener->subscribeOnSelection([this](const Vector2&) { onButtonClick(); });
	m_pOnClickListener->updateComponent();
}

/////////////////////////////////////////////////
unsigned int UIButton::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void UIButton::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
	
	}
	break;
	}
}

/////////////////////////////////////////////////
void UIButton::updateComponent()
{
}

/////////////////////////////////////////////////
void UIButton::onButtonClick()
{
	GetSystem()->GetLogger()->Log("UIButton::onButtonClick()");
}
