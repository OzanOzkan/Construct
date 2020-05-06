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
	pEntity->setSize(spawnParams.width, spawnParams.height);
	pEntity->sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_INIT });

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
std::vector<IEntity*> CEntitySystem::getEntities()
{
	std::vector<IEntity*> retList;

	for (auto& entityMapEntry : m_entityList)
	{
		retList.push_back(entityMapEntry.second.get());
	}

	return retList;
}

/////////////////////////////////////////////////
IEntity* CEntitySystem::findEntity(const std::string& entityName)
{
	IEntity* pRetEntity = nullptr;

	for (auto& entity : m_entityList) {
		if (entity.second.get()->getName().compare(entityName) == 0) {
			pRetEntity = entity.second.get();
			break;
		}
	}

	return pRetEntity;
}

/////////////////////////////////////////////////
IEntity* CEntitySystem::findEntity(const int& entityId)
{
	IEntity* pRetEntity = nullptr;

	auto itFoundEntity = m_entityList.find(entityId);
	if (itFoundEntity != m_entityList.end()) {
		pRetEntity = itFoundEntity->second.get();
	}
	
	return pRetEntity;
}

/////////////////////////////////////////////////
void CEntitySystem::onUpdate()
{
	auto itr = m_entityList.begin();
	while (itr != m_entityList.end())
	{
		if (itr->second->IsMarkedToDelete())
		{
			itr->second->sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_DESTROY });
			itr = m_entityList.erase(itr);
		}
		else
		{
			itr->second->sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_UPDATE });
			++itr;
		}
			
	}
}