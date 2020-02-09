/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityBasicTypes.h>
#include <System/EntitySystem/IEntityComponent.h>

class CEntity final : public IEntity
{
public:
	CEntity(ISystem* systemContext);
	
	// IEntity
	int getID() const { return m_entityID; }
	void setID(const int& entityId) { m_entityID = entityId; }
	void setName(const std::string& name) { m_entityName = name; }
	std::string getName() const { return m_entityName; }
	void setActive(const bool& isActive) { m_isActive = isActive; }
	bool isActive() const { return m_isActive; }
	int getComponentCount() const { return m_entityComponents.size(); };
	void setPosition(const Vector2& position) { m_entityPosition = position; }
	const Vector2& getPosition() { return m_entityPosition; }

	void sendEvent(const SEntityEvent& event) override;
	void setTimer(const float& seconds) override;
	// ~IEntity

	void MarkToDelete() { m_isMarkedToDelete = true; }
	const bool& IsMarkedToDelete() const { return m_isMarkedToDelete; }

protected:
	void addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent) override;
	IEntityComponent* getEntityComponentInternal(const std::string& componentName) override;
	std::vector<IEntityComponent*> getEntityComponentsInternal(const std::string& componentName) override;

private:
	ISystem * GetSystem() { return m_pSystem; }
	void HandleEntityEventInternal(const SEntityEvent& event);

private:
	int m_entityID;
	std::string m_entityName;
	bool m_isActive;
	std::multimap<std::string, std::shared_ptr<IEntityComponent>> m_entityComponents;
	Vector2 m_entityPosition;
	bool m_isMarkedToDelete;
	bool m_timerSet;
	float m_timerSetTime;
	float m_timerSec;
};