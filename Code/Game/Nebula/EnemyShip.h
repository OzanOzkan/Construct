#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityComponent.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>
#include <EntityComponents/CollisionEntityComponent.h>

class CEnemyShip : public IEntityComponent
{
public:
	CEnemyShip();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const EEntityEvent& event) override;
	void updateComponent() override;

private:
	void onUpdateEvent();
	void onCollisionEvent();
	void explodeShip();
	void destroyShip();

private:
	int m_Health = 100;
	SpriteRendererEntityComponent* m_pSpriteRendererComponent = nullptr;
	CollisionEntityComponent* m_pCollisionComponent = nullptr;
};