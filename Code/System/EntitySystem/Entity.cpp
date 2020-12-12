#include "Entity.h"

#include <System/ITime.h>
#include <ILog.h>

#include <functional>

/////////////////////////////////////////////////
CEntity::CEntity(ISystem* systemContext)
	: m_entityID(-1)
	, m_entityName("")
	, m_isActive(true)
	, m_tag("")
	, m_entityComponents()
	, m_entityPosition(0.f, 0.f)
	, m_entityRotation(0)
	, m_width(0.f)
	, m_height(0.f)
	, m_isMarkedToDelete(false)
	, m_timerSec(0.f)
	, m_timerSet(false)
	, m_timerSetTime(0.f)
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
	case EEntityEvent::ENTITY_EVENT_PREUPDATE:
	{
		// Swipe entity components marked to delete.
		removeEntityComponentInternal();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		// Entity timer
		if (m_timerSet)
		{
			if (GetSystem()->GetTime()->GetSystemTime() - m_timerSetTime >= m_timerSec)
			{
				m_timerSet = false;
				sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_TIMER_TICK });
			}
		}
	}
	break;
	}
}

/////////////////////////////////////////////////
void CEntity::removeEntityComponentInternal()
{
	while (!m_componentsToDelete.empty()) {
		IEntityComponent* pComponentToRemove = m_componentsToDelete.front();
		for (auto itr = m_entityComponents.begin(); itr != m_entityComponents.end(); ++itr) {
			if (itr->second.get() == pComponentToRemove) {
				itr->second->onEvent(EEntityEvent::ENTITY_COMPONENT_REMOVED);
				m_entityComponents.erase(itr);
				break;
			}
		}

		m_componentsToDelete.pop();
	}
}

/////////////////////////////////////////////////
void CEntity::removeEntityComponent(IEntityComponent* pEntityComponent)
{
	m_componentsToDelete.push(pEntityComponent);
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
	m_timerSetTime = GetSystem()->GetTime()->GetSystemTime();
	m_timerSec = seconds;
}