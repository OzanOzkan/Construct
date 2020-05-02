#include "Rigidbody2D.h"

#include "../CollisionEntityComponent.h"
#include <Physics/IPhysics.h>
#include "ILog.h"

/////////////////////////////////////////////////
Rigidbody2D::Rigidbody2D()
	: m_isCollided(false)
{
}

/////////////////////////////////////////////////
void Rigidbody2D::Init()
{
}

/////////////////////////////////////////////////
unsigned int Rigidbody2D::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_COLLISION;
}

/////////////////////////////////////////////////
void Rigidbody2D::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		processUpdateEvent();
		m_isCollided = false;
	}
	break;
	case EEntityEvent::ENTITY_EVENT_COLLISION:
	{
		if (CollisionEntityComponent* pCollisionEntityComponent = getEntity()->getEntityComponent<CollisionEntityComponent>())
		{
			Vector2 collisionPoint = event.GetData<SPhysicsEventData>()->collisionPoint;
			Vector2 centerPoint = pCollisionEntityComponent->getCenter();

			if (collisionPoint.y > centerPoint.y)
				m_isCollided = true;
		}
	}
	break;
	}
}

/////////////////////////////////////////////////
void Rigidbody2D::updateComponent()
{
}

/////////////////////////////////////////////////
void Rigidbody2D::applyForce(const float & force)
{
	this->force = force;
	this->velocity = force;
	m_isCollided = false;
}

/////////////////////////////////////////////////
void Rigidbody2D::processUpdateEvent()
{
	if (force < 0.1f)
		m_isCollided = false;

	if (m_isCollided)
	{
		t = 0.0;
		dt = 0.1f;
		velocity = 0.0f;
		position = 0.0f;
		force = 0.1f;
		return;
	}

	if(t <= 10.0)
	{
		if (force < 0.1f)
		{
			force += 0.005f;
		}

		if (velocity > 0.0f)
		{
			velocity += 0.005f;
		}

		position = position + velocity * dt;
		velocity = velocity + (force / mass) * dt;
		t += dt;
	}

	getEntity()->setPosition(Vector2(getEntity()->getPosition().x, getEntity()->getPosition().y + position));
}
