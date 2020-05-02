/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>

#include <EntityComponents/CollisionEntityComponent.h>

class CMissile : public IEntityComponent
{
public:
	CMissile();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

private:
	void updateEvent();
	void destroyMissile();

private:
	SpriteRendererEntityComponent * m_pSpriteRendererComponent;
	SWindowSize m_windowSize;

	CollisionEntityComponent * m_pTestCollisionComponent = nullptr;
};

REGISTER_ENTITY_COMPONENT(CMissile);