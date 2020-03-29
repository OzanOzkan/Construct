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

	void onButtonClick();

private:
	SpriteRendererEntityComponent* m_pBackgroundRenderer;
	TextRendererEntityComponent* m_pTextRenderer;
	OnSelectionListenerEntityComponent* m_pOnClickListener;
};