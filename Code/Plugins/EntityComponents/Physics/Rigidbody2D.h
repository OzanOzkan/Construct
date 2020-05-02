#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityComponent.h>

class Rigidbody2D : public IEntityComponent
{
public:
	Rigidbody2D();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent & event) override;
	void updateComponent() override;

	void applyForce(const float& force);

private:
	void processUpdateEvent();

private:
	bool m_isCollided = false;

	double t = 0.0;
	float dt = 0.1f;

	float velocity = 0.0f;
	float position = 0.0f;
	float force = 0.1f;
	float mass = 0.1f;
};

REGISTER_ENTITY_COMPONENT(Rigidbody2D);