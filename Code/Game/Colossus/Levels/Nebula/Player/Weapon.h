#pragma once

#include <System/EntitySystem/IEntityComponent.h>

class CWeapon : public IEntityComponent
{
public:
	CWeapon();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

private:
	void spawnMissile();

private:
	float m_missleSpawnSpeed;
};

REGISTER_ENTITY_COMPONENT(CWeapon);