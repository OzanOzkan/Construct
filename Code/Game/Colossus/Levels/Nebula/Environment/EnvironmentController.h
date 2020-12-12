#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntityComponent.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>

class CEnvironmentController : public IEntityComponent
{
public:
	CEnvironmentController();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

private:
	void ConfigureBackground();
	void ProcessUpdateEvent();

private:
	int m_resW, m_resH;
	float m_enemySpawnTime;
	float m_previousEnemySpawnTime;
	float m_envObjectSpawnTime;
	float m_previousEnvObjectSpawnTime;
	SpriteRendererEntityComponent* m_pScrollingBgComponent;
};

REGISTER_ENTITY_COMPONENT(CEnvironmentController);