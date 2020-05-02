#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>
#include <EntityComponents/OnSelectionListenerEntityComponent.h>
#include <EntityComponents/CollisionEntityComponent.h>
#include "Weapon.h"

class CPlayerShip : public IEntityComponent
{
public:
	CPlayerShip();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

private:
	void movePlayer(const Vector2& toPosition);

private:
	SpriteRendererEntityComponent * m_pSpriteRendererComponent;
	OnSelectionListenerEntityComponent* m_pOnSelectionListenerEntityComponent;
	CollisionEntityComponent* m_pCollisionEntityComponent;
	CWeapon* m_pWeapon1;
	CWeapon* m_pWeapon2;
};

REGISTER_ENTITY_COMPONENT(CPlayerShip);