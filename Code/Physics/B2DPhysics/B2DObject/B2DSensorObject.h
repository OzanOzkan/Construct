#pragma once

#include "B2DObject.h"

class CB2DSensorObject final : public CB2DObject
{
public:
	CB2DSensorObject(ISystem* systemContext, const SCollisionListenerParams& params, b2Body* pB2Body);

	void PrePhysicsUpdate();

private:
	Vector2 m_relativePositionToEntity;
};