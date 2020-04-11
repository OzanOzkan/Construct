#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntityComponent.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>

class CIsometricaEnvironmentController : public IEntityComponent
{
public:
	CIsometricaEnvironmentController();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

private:
	std::vector<SpriteRendererEntityComponent*> m_tiles{};
};