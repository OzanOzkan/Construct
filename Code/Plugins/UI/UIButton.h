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
	float m_width;
	float m_height;
	std::string m_backgroundImage;
	std::string m_backgroundOnPressedImage;
	bool m_isPressed;
};