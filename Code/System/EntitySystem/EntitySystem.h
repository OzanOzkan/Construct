#pragma once

#include <System/EntitySystem/IEntitySystem.h>
#include "Entity.h"

#include <memory>
#include <set>

class CEntitySystem : public IEntitySystem
{
public:
	// IEntitySystem
	virtual IEntity* spawnEntity(const SEntitySpawnParams& spawnParams) override;
	virtual void removeEntity(IEntity* pEntity) override;
	virtual int getEntityCount() const override;
	// ~IEntitySystem

private:
	std::set<std::unique_ptr<CEntity>> m_entityList = {};
};