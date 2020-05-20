#pragma once

#include <System/EntitySystem/IEntityComponent.h>

class CBox2DTestLevelController final : public IEntityComponent
{
public:
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

private:
	void configureLevel();
	void processUpdateEvent();
	void spawnDynamicPhysicalEntity(const Vector2& position);
};

REGISTER_ENTITY_COMPONENT(CBox2DTestLevelController);