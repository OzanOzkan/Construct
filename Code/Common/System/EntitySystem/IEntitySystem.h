#pragma once

#include "IEntity.h"

struct SEntitySpawnParams
{

};

class IEntitySystem
{
public:
	virtual ~IEntitySystem(){}

	virtual IEntity* spawnEntity(const SEntitySpawnParams& spawnParams) = 0;
	virtual void removeEntity(IEntity* pEntity) = 0;
	virtual int getEntityCount() const = 0;
};