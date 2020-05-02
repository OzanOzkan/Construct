#include "UIButton.h"

#include <ILog.h>
#include <System/EntitySystem/IEntity.h>
#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
UIButton::UIButton()
	: m_pBackgroundRenderer(nullptr)
	, m_pTextRenderer(nullptr)
	, m_pOnClickListener(nullptr)
	, m_backgroundImage("")
	, m_backgroundOnPressedImage("")
	, m_isPressed(false)
{
}

/////////////////////////////////////////////////
void UIButton::Init()
{
	m_width = 300;
	m_height = 100;

	m_backgroundImage = GetSystem()->getFileManager()->getAssetsDirectory() + "Default/UI/buttonbg.png";
	m_backgroundOnPressedImage = GetSystem()->getFileManager()->getAssetsDirectory() + "Default/UI/buttonbg_pressed.png";

	m_pBackgroundRenderer = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	m_pBackgroundRenderer->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Default/UI/buttonbg.png");
	m_pBackgroundRenderer->setLayerId(80);
	m_pBackgroundRenderer->setSize(m_height, m_width);
	m_pBackgroundRenderer->updateComponent();
	//m_pBackgroundRenderer->getSize(m_height, m_width);

	m_pTextRenderer = getEntity()->addEntityComponent<TextRendererEntityComponent>();
	m_pTextRenderer->setFontSize(20);
	m_pTextRenderer->setText("Button");
	m_pTextRenderer->setLayerId(81);
	m_pTextRenderer->setColor(RGBAColor(0, 0, 0, 1));
	m_pTextRenderer->updateComponent();

	m_pOnClickListener = getEntity()->addEntityComponent<OnSelectionListenerEntityComponent>();
	m_pOnClickListener->setSize(m_width, m_height);
	m_pOnClickListener->subscribeOnSelection(
		[this](const bool& isSelected, const Vector2& selectionPos) { 
			onButtonPressed(isSelected, selectionPos); 
	});
	//m_pOnClickListener->setDebugDraw(true);
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
		if (m_isPressed) 
			m_pBackgroundRenderer->setFile(m_backgroundOnPressedImage);
		else
			m_pBackgroundRenderer->setFile(m_backgroundImage);
	}
	break;
	}

	m_pBackgroundRenderer->setActive(m_isActive);
	m_pTextRenderer->setActive(m_isActive);
	m_pOnClickListener->setActive(m_isActive);
}

/////////////////////////////////////////////////
void UIButton::updateComponent()
{
	m_pBackgroundRenderer->setFile(m_backgroundImage);
	m_pBackgroundRenderer->setPosition(getPosition());
	m_pBackgroundRenderer->setRotation(getRotation());
	m_pBackgroundRenderer->setSize(m_height, m_width);
	m_pBackgroundRenderer->updateComponent();

	m_pTextRenderer->setPosition(Vector2(getPosition().x + (m_width / 2), getPosition().y + (m_height / 2)));
	m_pTextRenderer->updateComponent();

	m_pOnClickListener->setPosition(getPosition());
	m_pOnClickListener->setSize(m_width, m_height);
	m_pOnClickListener->updateComponent();
}

/////////////////////////////////////////////////
void UIButton::setSize(const float& width, const float& height)
{
	m_width = width;
	m_height = height;
}

/////////////////////////////////////////////////
void UIButton::setText(const std::string & text)
{
	m_pTextRenderer->setText(text);
	m_pTextRenderer->updateComponent();
}

/////////////////////////////////////////////////
void UIButton::setTextFontSize(const float & fontSize)
{
	m_pTextRenderer->setFontSize(fontSize);
	m_pTextRenderer->updateComponent();
}

/////////////////////////////////////////////////
void UIButton::setBackgroundImage(const std::string & file, const std::string& onPressedFile)
{
	m_backgroundImage = file;
	m_backgroundOnPressedImage = onPressedFile.compare("") ? onPressedFile : file;
}

/////////////////////////////////////////////////
void UIButton::subscribeToPressEvent(TSelectionEventCallbackFn fn)
{
	m_pOnClickListener->subscribeOnSelection(fn);
}

/////////////////////////////////////////////////
void UIButton::onButtonPressed(const bool& isPressed, const Vector2& selectionPos)
{
	m_isPressed = isPressed;
}
