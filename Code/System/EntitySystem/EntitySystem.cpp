/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "EntitySystem.h"


/////////////////////////////////////////////////
IEntity * CEntitySystem::spawnEntity(const SEntitySpawnParams & spawnParams)
{
	std::shared_ptr<CEntity> pEntity = std::make_shared<CEntity>();
	pEntity->setName(spawnParams.entityName);
	m_entityList.emplace(pEntity);

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
