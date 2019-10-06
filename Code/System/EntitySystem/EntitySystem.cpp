/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "EntitySystem.h"


CEntitySystem::CEntitySystem(SEnvironment * env)
	: m_pEnv(env)
{
}

/////////////////////////////////////////////////
IEntity * CEntitySystem::spawnEntity(const SEntitySpawnParams & spawnParams)
{
	std::shared_ptr<CEntity> pEntity = std::make_shared<CEntity>(m_pEnv);
	pEntity->setName(spawnParams.entityName);
	m_entityList.emplace(pEntity);

	pEntity->sendEvent(EEntityEvent::ENTITY_EVENT_INIT);

	return pEntity.get();
}

/////////////////////////////////////////////////
void CEntitySystem::removeEntity(IEntity * pEntity)
{

}

/////////////////////////////////////////////////
int CEntitySystem::getEntityCount() const
{
	return m_entityList.size();
}

/////////////////////////////////////////////////
void CEntitySystem::addEntityEventListener(IEntity * pEntity)
{
	m_eventListeners.emplace(pEntity);
}

/////////////////////////////////////////////////
void CEntitySystem::removeEntityEventListener(IEntity * pEntity)
{
	m_eventListeners.erase(pEntity);
}

/////////////////////////////////////////////////
void CEntitySystem::onUpdate()
{
	for (auto pEntity : m_entityList)
	{
		pEntity->sendEvent(EEntityEvent::ENTITY_EVENT_UPDATE);
	}
}
