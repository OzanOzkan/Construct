#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "../System/EntitySystem/IEntity.h"

enum class EPhysics : int
{
	NONE = 0,
	BOX2D
};

enum class EPhysicalObjectType : short
{
	RIGIDBODY2D = 0,
	COLLISION_LISTENER
};

struct S2DPhysicalizeParams
{
	IEntity* pEntity;
	float mass;
	float density = 1.0f;
	float friction = 0.1f;
	Vector2 bbox{ 1.f, 1.f };
	bool isDynamic = true;
	bool isRotationLocked = false;
};

struct SCollisionListenerParams
{
	IEntity* pEntity;
	int w, h = -1;
	Vector2 relativePosToEntity{ 0.f, 0.f };
};

struct SPhysicsEventData
{
	enum class EContactType {
		BEGIN_CONTACT = 0,
		END_CONTACT
	};

	IEntity* pEntity1 = nullptr;
	IEntity* pEntity2 = nullptr;
	Vector2 collisionPoint{ 0,0 };
	EContactType contactType = EContactType::BEGIN_CONTACT;
};

class IPhysicalObject
{
public:
	virtual ~IPhysicalObject() {}

	virtual void ApplyForce(const Vector2& force) = 0;
	virtual void ApplyLinearImpulse(const Vector2& impulse) = 0;
	virtual void SetRotationLock(const float& isEnabled) = 0;
	virtual void SetDynamic(const float& isDynamic) = 0;
};

class IPhysics : public IModule
{
public:
	virtual ~IPhysics() {}

	// 2D Basic Physics
	virtual IPhysicalObject* EnablePhysics2D(const S2DPhysicalizeParams& params) = 0;
	virtual IPhysicalObject* GetPhysicalObject(IEntity* pEntity) = 0;
	virtual void RemovePhysicalObject(IEntity* pEntity) = 0;
	// ~2D Basic Physics

	// 2D Collision
	virtual bool AddCollisionListener(const SCollisionListenerParams& params) = 0;
	virtual void RemoveCollisionListener(IEntity* pEntity) = 0;
	// ~2D Collision
};