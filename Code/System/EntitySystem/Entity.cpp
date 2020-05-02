#include "Entity.h"

#include <ILog.h>

#include <functional>

/////////////////////////////////////////////////
CEntity::CEntity(ISystem * systemContext)
	: m_entityID (-1)
	, m_entityName("")
	, m_isActive(true)
	, m_tag("")
	, m_entityComponents()
	, m_entityPosition(0.f, 0.f)
	, m_width(0.f)
	, m_height(0.f)
	, m_isMarkedToDelete(false)
	, m_timerSet(false)
	, m_timerSetTime(-1)
{
	m_pSystem = systemContext;
}

/////////////////////////////////////////////////
void CEntity::setSize(const float & width, const float & height)
{
	m_width = width;
	m_height = height;
}

/////////////////////////////////////////////////
void CEntity::getSize(float & width, float & height)
{
	width = m_width;
	height = m_height;
}

/////////////////////////////////////////////////
void CEntity::sendEvent(const SEntityEvent & event)
{
	// Handle event for this entity
	HandleEntityEventInternal(event);

	// Send event to components
	for (const auto& pComponentEntry : m_entityComponents)
	{
		const auto& pComponent = pComponentEntry.second;

		if (pComponent->getEventMask() & event.GetEvent())
		{
			pComponent->onEvent(event);
		}
	}
}

/////////////////////////////////////////////////
void CEntity::HandleEntityEventInternal(const SEntityEvent& event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		// Entity timer
		if (m_timerSet)
		{
			if (GetSystem()->getTime() - m_timerSetTime >= m_timerSec)
			{
				sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_TIMER_TICK });
				m_timerSet = false;
			}
		}
	}
	break;
	}
}

/////////////////////////////////////////////////
void CEntity::addEntityComponentInternal(const std::string& componentName, std::unique_ptr<IEntityComponent> entityComponent)
{
	m_entityComponents.emplace(std::make_pair(componentName, std::move(entityComponent)));
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

	for (const auto& componentPair : m_entityComponents)
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