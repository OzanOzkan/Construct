#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityComponent.h>

class CPlayer : public IEntityComponent
{
public:
	CPlayer();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent
};