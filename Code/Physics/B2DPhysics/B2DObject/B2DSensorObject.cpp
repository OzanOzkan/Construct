#include "B2DSensorObject.h"

/////////////////////////////////////////////////
CB2DSensorObject::CB2DSensorObject(const SCollisionListenerParams& params, b2Body* pB2Body)
	: CB2DObject(params.pEntity, Vector2(params.w, params.h), false, true, pB2Body)
	, m_relativePositionToEntity(params.relativePosToEntity)
{
}

/////////////////////////////////////////////////
void CB2DSensorObject::PrePhysicsUpdate()
{
	Vector2 position = m_pEntity->getPosition() + m_relativePositionToEntity;
	m_pB2Body->SetTransform(b2Vec2((position.x + m_bbox.x / 2) * m_P2M, (position.y + m_bbox.y / 2) * m_P2M), m_pB2Body->GetAngle());
}