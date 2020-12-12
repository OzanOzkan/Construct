#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include "../EntityComponents/SpriteRendererEntityComponent.h"
#include "../EntityComponents/TextRendererEntityComponent.h"
#include "../EntityComponents/OnSelectionListenerEntityComponent.h"

class UIButton : public IEntityComponent
{
public:
	UIButton();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

	void getClassDesc(std::map<std::string, void*>& desc) {
		desc.emplace("width", &m_width);
		desc.emplace("height", &m_height);
		desc.emplace("fontSize", &m_fontSize);
		desc.emplace("buttonText", &m_buttonText);
		desc.emplace("backgroundImage", &m_backgroundImage);
		desc.emplace("backgroundOnPressedImage", &m_backgroundOnPressedImage);
	}

	void setSize(const float& width, const float& height);
	void setText(const std::string& text);
	void setTextFontSize(const float& fontSize);
	void setBackgroundImage(const std::string& file, const std::string& onPressedFile = "");
	void subscribeToPressEvent(TSelectionEventCallbackFn fn);

private:
	void onButtonPressed(const bool& isPressed, const Vector2& selectionPos);

private:
	SpriteRendererEntityComponent* m_pBackgroundRenderer;
	TextRendererEntityComponent* m_pTextRenderer;
	OnSelectionListenerEntityComponent* m_pOnClickListener;
	int m_width;
	int m_height;
	int m_fontSize;
	std::string m_buttonText;
	std::string m_backgroundImage;
	std::string m_backgroundOnPressedImage;
	bool m_isPressed;
};

REGISTER_ENTITY_COMPONENT(UIButton);