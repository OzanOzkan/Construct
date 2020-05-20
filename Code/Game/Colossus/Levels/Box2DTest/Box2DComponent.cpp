#include "Box2DComponent.h"

#include <System/EntitySystem/IEntity.h>

/////////////////////////////////////////////////
CBox2DComponent::CBox2DComponent()
	: m_pPhysicalObject(nullptr)
	, m_boundingBox({1.f,1.0f})
	, m_density(1.f)
	, m_friction(0.1f)
	, m_isDynamic(true)
{
}

/////////////////////////////////////////////////
void CBox2DComponent::Init()
{

}

/////////////////////////////////////////////////
unsigned int CBox2DComponent::getEventMask() const
{
	return ENTITY_EVENT_UPDATE | ENTITY_LEVEL_LOAD_END;
}

/////////////////////////////////////////////////
void CBox2DComponent::onEvent(const SEntityEvent& event)
{
	if (event.GetEvent() == ENTITY_LEVEL_LOAD_END) {
		createPhysicalizedObject();
	}
}

/////////////////////////////////////////////////
void CBox2DComponent::updateComponent()
{
	createPhysicalizedObject();
}

/////////////////////////////////////////////////
void CBox2DComponent::applyForce(const Vector2& force)
{
	if (m_pPhysicalObject) {
		m_pPhysicalObject->ApplyForce(force);
	}
}

/////////////////////////////////////////////////
void CBox2DComponent::applyLinearImpulse(const Vector2& impulse)
{
	if (m_pPhysicalObject) {
		m_pPhysicalObject->ApplyLinearImpulse(impulse);
	}
}

/////////////////////////////////////////////////
void CBox2DComponent::createPhysicalizedObject()
{
	if (m_pPhysicalObject) {
		GetSystem()->GetPhysics()->RemovePhysicalObject(getEntity());
	}

	S2DPhysicalizeParams params;
	params.pEntity = getEntity();
	params.density = m_density;
	params.friction = m_friction;
	params.bbox = m_boundingBox;
	params.isDynamic = m_isDynamic;

	m_pPhysicalObject = GetSystem()->GetPhysics()->EnablePhysics2D(params);
}
