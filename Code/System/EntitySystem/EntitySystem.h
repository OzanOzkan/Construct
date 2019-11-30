/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/EntitySystem/IEntitySystem.h>
#include "Entity.h"

#include <memory>
#include <set>
#include <vector>

class CEntitySystem : public IEntitySystem
{
public:
	CEntitySystem(ISystem* systemContext);

	// IEntitySystem
	IEntity* spawnEntity(const SEntitySpawnParams& spawnParams) override;
	void removeEntity(IEntity* pEntity) override;
	int getEntityCount() const override;
	void addEntityEventListener(IEntity* pEntity) override;
	void removeEntityEventListener(IEntity* pEntity) override;
	// ~IEntitySystem

	void onUpdate() override;

private:
	ISystem * m_pSystem = nullptr;
	std::set<std::shared_ptr<CEntity>> m_entityList = {};
	std::set<IEntity*> m_eventListeners = {};
};