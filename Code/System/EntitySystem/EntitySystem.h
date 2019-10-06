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
	CEntitySystem(SEnvironment* env);

	// IEntitySystem
	virtual IEntity* spawnEntity(const SEntitySpawnParams& spawnParams) override;
	virtual void removeEntity(IEntity* pEntity) override;
	virtual int getEntityCount() const override;
	virtual void addEntityEventListener(IEntity* pEntity) override;
	virtual void removeEntityEventListener(IEntity* pEntity) override;
	// ~IEntitySystem

	virtual void onUpdate() override;

private:
	SEnvironment * m_pEnv = nullptr;
	std::set<std::shared_ptr<CEntity>> m_entityList = {};
	std::set<IEntity*> m_eventListeners = {};
};