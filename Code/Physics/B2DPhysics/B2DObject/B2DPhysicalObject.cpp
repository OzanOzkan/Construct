#include "B2DPhysicalObject.h"

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

/////////////////////////////////////////////////
CB2DPhysicalObject::CB2DPhysicalObject(ISystem* systemContext, const S2DPhysicalizeParams& params, b2Body* pB2Body)
	: CB2DObject(systemContext, params.pEntity, params.bbox, params.isRotationLocked, params.isDynamic, pB2Body)
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
	CB2DObject::PrePhysicsUpdate();

	// Update physical object position and rotation with entity's actual position and rotation right before physical calculations. 
	Vector2 entityPosition((m_pEntity->getPosition().x + m_bbox.x / 2) * m_P2M, (m_pEntity->getPosition().y + m_bbox.y / 2) * m_P2M);
	m_pB2Body->SetTransform(b2Vec2(entityPosition.x, entityPosition.y), m_pB2Body->GetAngle());
}

/////////////////////////////////////////////////
void CB2DPhysicalObject::PostPhysicsUpdate()
{
	CB2DObject::PostPhysicsUpdate();

	// If physical object is a dynamic body, update world position and rotation
	if (m_pB2Body->GetType() == b2_dynamicBody) {
		if (!m_isRotationLocked) {
			m_pEntity->setRotation(GetFRotation());
		}

		m_pEntity->setPosition(GetVector2Position());
	}
}