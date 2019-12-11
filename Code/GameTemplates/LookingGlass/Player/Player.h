#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>
#include "Weapon.h"

class CPlayer : public IEntityComponent
{
public:
	CPlayer();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const EEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

private:
	SpriteRendererEntityComponent * m_pSpriteRendererComponent;
	CWeapon* m_pWeapon1;
	CWeapon* m_pWeapon2;
};