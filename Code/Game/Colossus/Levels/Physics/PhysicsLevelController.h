#pragma once

#include <System/EntitySystem/IEntityComponent.h>

class CPhysicsLevelController : public IEntityComponent 
{
public:
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

private:
	void setupLevel();
	void physicalizedObjectSpawner();
};

REGISTER_ENTITY_COMPONENT(CPhysicsLevelController);