/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IEntity.h"

struct SEntitySpawnParams
{
	std::string entityName = "";
};

class IEntitySystem
{
public:
	virtual ~IEntitySystem(){}

	virtual IEntity* spawnEntity(const SEntitySpawnParams& spawnParams) = 0;
	virtual void removeEntity(IEntity* pEntity) = 0;
	virtual int getEntityCount() const = 0;
};