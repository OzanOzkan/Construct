#pragma once

#include <System/ISystem.h>
#include <Physics/IPhysics.h>

#include "B2DObject/B2DPhysicalObject.h"
#include "B2DObject/B2DSensorObject.h"

#include <box2d/b2_world.h>
#include <box2d/b2_contact_manager.h>

#include <memory>
#include <vector>
#include <queue>

class CB2DPhysics : public IPhysics, public b2ContactListener
{
public:
	CB2DPhysics(ISystem* systemContext);

	void InitializeModule() override;
	void onPreUpdate() override;
	void onUpdate() override;
	void onPostUpdate() override;
	IPhysicalObject* EnablePhysics2D(const S2DPhysicalizeParams& params) override;
	IPhysicalObject* GetPhysicalObject(IEntity* pEntity) override;
	void RemovePhysicalObject(IEntity* pEntity) override;
	bool AddCollisionListener(const SCollisionListenerParams& params) override;
	void RemoveCollisionListener(IEntity* pEntity) override;

	// b2ContactListener
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	// ~b2ContactListener

protected:
	std::unique_ptr<CB2DPhysicalObject> createPhysicalObject(const S2DPhysicalizeParams& params);
	std::unique_ptr<CB2DSensorObject> createSensorObject(const SCollisionListenerParams& params);
	void PhysicalObjectsPrePhysicsUpdate();
	void PhysicalObjectsPostPhysicsUpdate();
	void SensorObjectsPrePhysicsUpdate();
	void DispatchContactDataToEntites(b2Contact* contact, const SPhysicsEventData::EContactType& contactType);

protected:
	ISystem* getSystem() { return m_pSystem; }

private:
	enum class E2DPhysicsState {
		INIT = 0,
		PREUPDATE,
		ONUPDATE,
		POSTUPDATE
	};

private:
	ISystem* m_pSystem;
	std::unique_ptr<b2World> m_b2World;
	b2Vec2 m_gravity;
	int m_velocityIterations;
	int m_positionIterations;
	E2DPhysicsState m_currentState;
	std::vector<std::unique_ptr<CB2DPhysicalObject>> m_physicalObjects;
	std::vector<std::unique_ptr<CB2DSensorObject>> m_sensorObjects;
	std::queue<b2Body*> m_bodiesToRemove;
	const float m_M2P;
	const float m_P2M;
};