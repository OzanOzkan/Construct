#include "B2DPhysicalObject.h"

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

/////////////////////////////////////////////////
CB2DPhysicalObject::CB2DPhysicalObject(const S2DPhysicalizeParams& params, b2Body* pB2Body)
	: CB2DObject(params.pEntity, params.bbox, params.isRotationLocked, params.isDynamic, pB2Body)
	, m_density(params.density)
	, m_friction(params.friction)
{
}

/////////////////////////////////////////////////
void CB2DPhysicalObject::ApplyForce(const Vector2& force)
{
	m_pB2Body->ApplyForce(b2Vec2(force.x, force.y), m_pB2Body->GetWorldCenter(), true);
}

/////////////////////////////////////////////////
void CB2DPhysicalObject::ApplyLinearImpulse(const Vector2& impulse)
{
	m_pB2Body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), m_pB2Body->GetWorldCenter(), true);
}

/////////////////////////////////////////////////
void CB2DPhysicalObject::PrePhysicsUpdate()
{
	Vector2 entityPosition((m_pEntity->getPosition().x + m_bbox.x / 2) * m_P2M, (m_pEntity->getPosition().y + m_bbox.y / 2) * m_P2M);
	m_pB2Body->SetTransform(b2Vec2(entityPosition.x, entityPosition.y), m_pB2Body->GetAngle());
}

/////////////////////////////////////////////////
void CB2DPhysicalObject::PostPhysicsUpdate()
{
	// If physical object is a dynamic body, update world position and rotation
	if (m_pB2Body->GetType() == b2_dynamicBody) {
		b2Vec2 position = m_pB2Body->GetPosition();
		float rotation = m_pB2Body->GetAngle();

		if (!m_isRotationLocked) {
			// Radians to degrees (Radians * 180 / PI)
			m_pEntity->setRotation(rotation * 180 / 3.14);
		}

		// Center point to top left
		m_pEntity->setPosition(Vector2((position.x * m_M2P) - m_bbox.x / 2, (position.y * m_M2P) - m_bbox.y / 2));
	}
}