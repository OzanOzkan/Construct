#include "Rigidbody2D.h"

#include <System/EntitySystem/IEntity.h>

/////////////////////////////////////////////////
Rigidbody2D::Rigidbody2D()
	: m_pPhysicalObject(nullptr)
	, m_boundingBox({1.f,1.0f})
	, m_density(1.f)
	, m_friction(0.1f)
	, m_isDynamic(true)
{
}

/////////////////////////////////////////////////
void Rigidbody2D::Init()
{

}

/////////////////////////////////////////////////
unsigned int Rigidbody2D::getEventMask() const
{
	return ENTITY_EVENT_UPDATE | ENTITY_LEVEL_LOAD_END;
}

/////////////////////////////////////////////////
void Rigidbody2D::onEvent(const SEntityEvent& event)
{
	if (event.GetEvent() == ENTITY_LEVEL_LOAD_END) {
		createPhysicalizedObject();
	}
}

/////////////////////////////////////////////////
void Rigidbody2D::updateComponent()
{
	createPhysicalizedObject();
}

/////////////////////////////////////////////////
void Rigidbody2D::applyForce(const Vector2& force)
{
	if (m_pPhysicalObject) {
		m_pPhysicalObject->ApplyForce(force);
	}
}

/////////////////////////////////////////////////
void Rigidbody2D::applyLinearImpulse(const Vector2& impulse)
{
	if (m_pPhysicalObject) {
		m_pPhysicalObject->ApplyLinearImpulse(impulse);
	}
}

/////////////////////////////////////////////////
void Rigidbody2D::createPhysicalizedObject()
{
	removePhysicalizedObject();

	S2DPhysicalizeParams params;
	params.pEntity = getEntity();
	params.density = m_density;
	params.friction = m_friction;
	params.bbox = m_boundingBox;
	params.isDynamic = m_isDynamic;

	m_pPhysicalObject = GetSystem()->GetPhysics()->EnablePhysics2D(params);
}

/////////////////////////////////////////////////
void Rigidbody2D::removePhysicalizedObject()
{
	if (m_pPhysicalObject) {
		GetSystem()->GetPhysics()->RemovePhysicalObject(getEntity());
	}
}
