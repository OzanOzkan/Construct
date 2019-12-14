/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "EntitySystem.h"

/////////////////////////////////////////////////
CEntitySystem::CEntitySystem(ISystem * systemContext)
	: m_pSystem(systemContext)
	, m_entityList()
	, m_eventListeners()
{
}

/////////////////////////////////////////////////
IEntity * CEntitySystem::spawnEntity(const SEntitySpawnParams & spawnParams)
{
	std::unique_ptr<CEntity> pEntity = std::make_unique<CEntity>(m_pSystem);
	pEntity->setID(m_entityList.size() > 0 ? m_entityList.rbegin()->first + 1 : 0);
	pEntity->setName(spawnParams.entityName);
	pEntity->setPosition(spawnParams.position);
	pEntity->sendEvent(EEntityEvent::ENTITY_EVENT_INIT);

	return static_cast<IEntity*>(m_entityList.insert(
		std::make_pair(pEntity->getID(),
		std::move(pEntity))
	).first->second.get());
}

/////////////////////////////////////////////////
void CEntitySystem::destroyEntity(const int& entityId)
{
	// Send destroy event to components and mark entity for delete on the next frame.
	CEntity* pEntity = m_entityList.at(entityId).get();
	pEntity->sendEvent(EEntityEvent::ENTITY_EVENT_DESTROY);
	pEntity->MarkToDelete();
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
	auto itr = m_entityList.begin();
	while (itr != m_entityList.end())
	{
		if (itr->second->IsMarkedToDelete())
		{
			itr = m_entityList.erase(itr);
		}
		else
		{
			itr->second->sendEvent(EEntityEvent::ENTITY_EVENT_UPDATE);
			++itr;
		}
			
	}
}
