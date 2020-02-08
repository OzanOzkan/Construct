#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "../System/EntitySystem/IEntity.h"

enum class EPhysics : int
{
	NONE = 0,
	SDL2
};

struct SCollisionListenerParams
{
	IEntity* pEntity;
	int w, h = -1;
};

class IPhysics : public IModule
{
public:
	virtual ~IPhysics() {}

	// 2D Collision
	virtual bool AddCollisionListener(const SCollisionListenerParams& params) = 0;
	virtual void RemoveCollisionListener(IEntity* pEntity) = 0;
	// ~2D Collision
};