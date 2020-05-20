#pragma once 

#include <System/EntitySystem/IEntity.h>
#include <Physics/IPhysics.h>

#include <box2d/b2_body.h>

class CB2DObject : public IPhysicalObject
{
public:
	CB2DObject(IEntity* pEntity, const Vector2& bbox, 
		const bool& isRotationLocked, const bool& isDynamic, b2Body* pB2Body);

	void ApplyForce(const Vector2& force) override {}
	void ApplyLinearImpulse(const Vector2& impulse) override {}
	void SetRotationLock(const float& isLocked) override { m_isRotationLocked = isLocked; }
	void SetDynamic(const float& isDynamic) override { m_isDynamic = isDynamic; }

	IEntity* GetEntity() { return m_pEntity; }
	b2Body* GetB2Body() { return m_pB2Body; }

protected:
	IEntity* m_pEntity;
	Vector2 m_bbox;
	bool m_isDynamic;
	bool m_isRotationLocked;
	b2Body* m_pB2Body;
	const float m_M2P;
	const float m_P2M;
};