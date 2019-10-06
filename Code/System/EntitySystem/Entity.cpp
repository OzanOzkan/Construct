/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Entity.h"

/////////////////////////////////////////////////
CEntity::CEntity(SEnvironment * env)
{
	m_pEnv = env;
}

/////////////////////////////////////////////////
void CEntity::sendEvent(const EEntityEvent & event)
{
	for (auto pComponentEntry : m_entityComponents)
	{
		auto pComponent = pComponentEntry.second;

		if (pComponent->getEventMask() & event)
		{
			pComponent->onEvent(event);
		}
	}
}

/////////////////////////////////////////////////
void CEntity::addEntityComponentInternal(const std::string & componentName, std::shared_ptr<IEntityComponent> entityComponent)
{
	m_entityComponents.emplace(std::make_pair(componentName, entityComponent));
}

/////////////////////////////////////////////////
IEntityComponent * CEntity::getEntityComponentInternal(const std::string & componentName)
{
	return m_entityComponents[componentName].get();
}
