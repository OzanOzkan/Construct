#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>

class CMissile : public IEntityComponent
{
public:
	CMissile();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const EEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

private:
	void updateEvent();

private:
	SpriteRendererEntityComponent * m_pSpriteRendererComponent;
};