#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Physics/IPhysics.h>

class CBox2DComponent : public IEntityComponent
{
public:
	CBox2DComponent();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

	void getClassDesc(std::map<std::string, void*>& desc) {
		desc.emplace("width", &m_boundingBox.x);
		desc.emplace("height", &m_boundingBox.y);
		desc.emplace("density", &m_density);
		desc.emplace("friction", &m_friction);
		desc.emplace("isDynamic", &m_isDynamic);
	}

	void setBoundingBox(const Vector2& boundingBox) { m_boundingBox = boundingBox; }
	void setDensity(const float& density) { m_density = density; }
	void setFriction(const float& friction) { m_friction = friction; }
	void setDynamic(const bool& isDynamic) { m_isDynamic = isDynamic; }
	
	void applyForce(const Vector2& force);
	void applyLinearImpulse(const Vector2& impulse);

private:
	void createPhysicalizedObject();
	void removePhysicalizedObject();

private:
	IPhysicalObject* m_pPhysicalObject;
	Vector2 m_boundingBox;
	float m_density;
	float m_friction;
	bool m_isDynamic;
};

REGISTER_ENTITY_COMPONENT(CBox2DComponent);