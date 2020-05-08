#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityComponent.h>

class CPlayerView : public IEntityComponent
{
public:
	CPlayerView();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent
};

REGISTER_ENTITY_COMPONENT(CPlayerView);