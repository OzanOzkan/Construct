#include "B2DPhysics.h"

#include <ILog.h>

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

/////////////////////////////////////////////////
CB2DPhysics::CB2DPhysics(ISystem* systemContext)
	: m_pSystem(systemContext)
	, m_b2World(nullptr)
	, m_gravity(0.0f, 9.8f)
	, m_velocityIterations(8)
	, m_positionIterations(3)
	, m_currentState(E2DPhysicsState::INIT)
	, m_M2P(40)
	, m_P2M(1/m_M2P)
{
}

/////////////////////////////////////////////////
void CB2DPhysics::InitializeModule()
{
	// Create physics world
	m_b2World = std::make_unique<b2World>(m_gravity);

	// Set contact listener for sensors
	m_b2World->SetContactListener(this);
}

/////////////////////////////////////////////////
void CB2DPhysics::onUpdate()
{
	m_currentState = E2DPhysicsState::ONUPDATE;

	// Override physical object positions with actual entity positions before physics calculation
	PhysicalObjectsPrePhysicsUpdate();
	SensorObjectsPrePhysicsUpdate();

	// Update physics simulation
	m_b2World->Step(getSystem()->GetTime()->GetDeltaTime(), m_velocityIterations, m_positionIterations);

	// Update physical objects with their new object and rotation
	PhysicalObjectsPostPhysicsUpdate();
}

/////////////////////////////////////////////////
void CB2DPhysics::onPostUpdate()
{
	m_currentState = E2DPhysicsState::POSTUPDATE;
}

/////////////////////////////////////////////////
void CB2DPhysics::onPreUpdate()
{
	m_currentState = E2DPhysicsState::PREUPDATE;

	// Sweep queue of marked bodies to remove
	while (!m_bodiesToRemove.empty()) {
		m_b2World->DestroyBody(m_bodiesToRemove.front());
		m_bodiesToRemove.pop();
	}
}

/////////////////////////////////////////////////
IPhysicalObject* CB2DPhysics::EnablePhysics2D(const S2DPhysicalizeParams& params)
{
	return m_physicalObjects.emplace_back(createPhysicalObject(params)).get();
}

/////////////////////////////////////////////////
IPhysicalObject* CB2DPhysics::GetPhysicalObject(IEntity* pEntity)
{
	IPhysicalObject* pPhysicalObject = nullptr;

	for (auto itr = m_physicalObjects.begin(); itr != m_physicalObjects.end(); ++itr) {
		if (itr->get()->GetEntity() == pEntity) {
			pPhysicalObject = itr->get();
			break;
		}
	}

	return pPhysicalObject;
}

/////////////////////////////////////////////////
void CB2DPhysics::RemovePhysicalObject(IEntity* pEntity)
{
	for (auto itr = m_physicalObjects.begin(); itr != m_physicalObjects.end(); ++itr) {
		if (itr->get()->GetEntity() == pEntity) {
			m_bodiesToRemove.push(itr->get()->GetB2Body());
			m_physicalObjects.erase(itr);
			break;
		}
	}
}

/////////////////////////////////////////////////
bool CB2DPhysics::AddCollisionListener(const SCollisionListenerParams& params)
{
	if (m_sensorObjects.emplace_back(createSensorObject(params)).get()) {
		return true;
	}
	else {
		return false;
	}
}

/////////////////////////////////////////////////
void CB2DPhysics::RemoveCollisionListener(IEntity* pEntity)
{
	for (auto itr = m_sensorObjects.begin(); itr != m_sensorObjects.end(); ++itr) {
		if (itr->get()->GetEntity() == pEntity) {
			m_bodiesToRemove.push(itr->get()->GetB2Body());
			m_sensorObjects.erase(itr);
			break;
		}
	}
}

/////////////////////////////////////////////////
std::unique_ptr<CB2DPhysicalObject> CB2DPhysics::createPhysicalObject(const S2DPhysicalizeParams& params)
{
	b2BodyDef bodyDef;
	bodyDef.type = params.isDynamic ? b2_dynamicBody : b2_staticBody;

	// Box2D uses center point as a position. Convert top left corner pos to center pos
	bodyDef.position.Set((params.pEntity->getPosition().x + params.bbox.x / 2) * m_P2M, 
		(params.pEntity->getPosition().y + params.bbox.y / 2) * m_P2M);

	b2PolygonShape bbox;
	bbox.SetAsBox((params.bbox.x / 2) * m_P2M, (params.bbox.y / 2) * m_P2M);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bbox;
	fixtureDef.density = params.density;
	fixtureDef.friction = params.friction;

	b2Body* body = m_b2World->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef)->SetUserData((void*)params.pEntity);

	return std::make_unique<CB2DPhysicalObject>(m_pSystem, params, body);
}

/////////////////////////////////////////////////
std::unique_ptr<CB2DSensorObject> CB2DPhysics::createSensorObject(const SCollisionListenerParams& params)
{
	b2PolygonShape bbox;
	bbox.SetAsBox((params.w / 2) * m_P2M, (params.h / 2) * m_P2M);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bbox;
	fixtureDef.isSensor = true;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;

	Vector2 position = params.pEntity->getPosition() + params.relativePosToEntity;
	bodyDef.position.Set((position.x + params.w / 2) * m_P2M, (position.y + params.h / 2) * m_P2M);

	b2Body* sensorBody = m_b2World->CreateBody(&bodyDef);
	sensorBody->CreateFixture(&fixtureDef)->SetUserData((void*)params.pEntity);

	return std::make_unique<CB2DSensorObject>(m_pSystem, params, sensorBody);
}

/////////////////////////////////////////////////
void CB2DPhysics::PhysicalObjectsPrePhysicsUpdate()
{
	for (auto& physicalObject : m_physicalObjects) {
		physicalObject->PrePhysicsUpdate();
	}
}

/////////////////////////////////////////////////
void CB2DPhysics::PhysicalObjectsPostPhysicsUpdate()
{
	for (auto& physicalObject : m_physicalObjects) {
		physicalObject->PostPhysicsUpdate();
	}
}

/////////////////////////////////////////////////
void CB2DPhysics::SensorObjectsPrePhysicsUpdate()
{
	for (auto& sensorObject : m_sensorObjects) {
		sensorObject->PrePhysicsUpdate();
	}
}

/////////////////////////////////////////////////
void CB2DPhysics::BeginContact(b2Contact* contact)
{
	DispatchContactDataToEntites(contact, SPhysicsEventData::EContactType::BEGIN_CONTACT);
}

/////////////////////////////////////////////////
void CB2DPhysics::EndContact(b2Contact* contact)
{
	DispatchContactDataToEntites(contact, SPhysicsEventData::EContactType::END_CONTACT);
}

/////////////////////////////////////////////////
void CB2DPhysics::DispatchContactDataToEntites(b2Contact* contact, const SPhysicsEventData::EContactType& contactType)
{
	if (m_currentState == E2DPhysicsState::ONUPDATE) {
		IEntity* pEntity1 = static_cast<IEntity*>(contact->GetFixtureA()->GetUserData());
		IEntity* pEntity2 = static_cast<IEntity*>(contact->GetFixtureB()->GetUserData());

		if (pEntity1 && pEntity2) {
			SPhysicsEventData data;
			data.pEntity1 = pEntity1;
			data.pEntity2 = pEntity2;
			data.contactType = contactType;

			b2WorldManifold contactPoint;
			contact->GetWorldManifold(&contactPoint);
			data.collisionPoint = Vector2(contactPoint.points[0].x * m_M2P, contactPoint.points[0].y * m_M2P);

			pEntity1->sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_COLLISION, &data });
			pEntity2->sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_COLLISION, &data });
		}
	}
}
