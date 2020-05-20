#pragma once

#include "B2DObject.h"

class CB2DPhysicalObject final : public CB2DObject
{
public:
	CB2DPhysicalObject(const S2DPhysicalizeParams& params, b2Body* pB2Body);

	void ApplyForce(const Vector2& force) override;
	void ApplyLinearImpulse(const Vector2& impulse) override;

	void PrePhysicsUpdate();
	void PostPhysicsUpdate();

private:
	float m_density;
	float m_friction;
};