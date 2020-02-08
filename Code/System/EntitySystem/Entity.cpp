/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Entity.h"

#include <ILog.h>

#include <functional>

/////////////////////////////////////////////////
CEntity::CEntity(ISystem * systemContext)
	: m_entityID (-1)
	, m_entityName("")
	, m_isActive(true)
	, m_entityComponents()
	, m_entityPosition(0.f, 0.f)
	, m_isMarkedToDelete(false)
	, m_timerSet(false)
	, m_timerSetTime(-1)
{
	m_pSystem = systemContext;
}

/////////////////////////////////////////////////
void CEntity::sendEvent(const EEntityEvent & event)
{
	// Handle event for this entity
	HandleEntityEventInternal(event);

	// Send event to components
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
void CEntity::HandleEntityEventInternal(const EEntityEvent& event)
{
	switch (event)
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		// Entity timer
		if (m_timerSet)
		{
			if (GetSystem()->getTime() - m_timerSetTime >= m_timerSec)
			{
				sendEvent(EEntityEvent::ENTITY_EVENT_TIMER_TICK);
				m_timerSet = false;
			}
		}
	}
	break;
	}
}

/////////////////////////////////////////////////
void CEntity::addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent)
{
	m_entityComponents.emplace(std::make_pair(componentName, entityComponent));
}

/////////////////////////////////////////////////
IEntityComponent * CEntity::getEntityComponentInternal(const std::string& componentName)
{
	return m_entityComponents.find(componentName)->second.get();
}

/////////////////////////////////////////////////
std::vector<IEntityComponent*> CEntity::getEntityComponentsInternal(const std::string& componentName)
{
	std::vector<IEntityComponent*> retVec{};

	for (auto componentPair : m_entityComponents)
	{
		if (componentPair.first.compare(componentName) == 0)
			retVec.push_back(componentPair.second.get());
	}

	return retVec;
}

/////////////////////////////////////////////////
void CEntity::setTimer(const float& seconds)
{
	m_timerSet = true;
	m_timerSetTime = GetSystem()->getTime();
	m_timerSec = seconds;
}