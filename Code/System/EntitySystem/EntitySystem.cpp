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

//std::map<std::string, EntityComponentFactory::TCreateMethod> EntityComponentFactory::s_methods;
//std::map<std::string, EntityComponentFactory::EntityComponentDescriptor> m_descriptors;
//
//bool EntityComponentFactory::Register(const std::string name, EntityComponentFactory::TCreateMethod funcCreate)
//{
//	if (auto it = s_methods.find(name); it == s_methods.end())
//	{ // C++17 init-if ^^
//		s_methods[name] = funcCreate;
//		return true;
//	}
//	return false;
//}
//
//std::unique_ptr<IEntityComponent> EntityComponentFactory::Create(const std::string& name)
//{
//	std::unique_ptr<IEntityComponent> retComponent = nullptr;
//
//	if (auto it = s_methods.find(name); it != s_methods.end()) {
//		retComponent = it->second(); // call the createFunc
//		
//		EntityComponentFactory::EntityComponentDescriptor desc;
//		retComponent->getDescriptor(desc);
//		m_descriptors.emplace(name, desc);
//
//		return std::move(retComponent);
//	}
//	return nullptr;
//}
//
//EntityComponentFactory::EntityComponentDescriptor EntityComponentFactory::getDescriptor(const std::string& name)
//{
//	if (auto it = m_descriptors.find(name); it != m_descriptors.end())
//		return it->second; // call the createFunc
//
//	return EntityComponentFactory::EntityComponentDescriptor{};
//}