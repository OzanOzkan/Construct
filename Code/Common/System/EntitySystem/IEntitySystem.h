/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IEntity.h"

struct SEntitySpawnParams
{
	std::string entityName = "";
	Vector2 position{ 0, 0 };
};

class IEntitySystem
{
public:
	virtual ~IEntitySystem(){}

	virtual IEntity* spawnEntity(const SEntitySpawnParams& spawnParams) = 0;
	virtual void destroyEntity(const int& entityId) = 0;
	virtual int getEntityCount() const = 0;
	virtual void addEntityEventListener(IEntity* pEntity) = 0;
	virtual void removeEntityEventListener(IEntity* pEntity) = 0;

	// Will be removed.
	virtual void onUpdate() = 0;
};