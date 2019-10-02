#include "EntitySystem.h"


/////////////////////////////////////////////////
IEntity * CEntitySystem::spawnEntity(const SEntitySpawnParams & spawnParams)
{
//	std::unique_ptr<CEntity> newEntity = std::make_unique<CEntity>();
	m_entityList.emplace(std::make_unique<CEntity>());

	return nullptr;
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
