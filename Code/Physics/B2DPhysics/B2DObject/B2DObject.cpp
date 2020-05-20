#include "B2DObject.h"

CB2DObject::CB2DObject(IEntity* pEntity, const Vector2& bbox, 
	const bool& isRotationLocked, const bool& isDynamic, b2Body* pB2Body)
	: m_pEntity(pEntity)
	, m_bbox(bbox)
	, m_isRotationLocked(isRotationLocked)
	, m_isDynamic(isDynamic)
	, m_pB2Body(pB2Body)
	, m_M2P(40)
	, m_P2M(1 / m_M2P)
{
}