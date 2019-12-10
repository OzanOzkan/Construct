/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IEntityComponent.h"
#include "../../Math/Math.h"

#include <string>
#include <map>
#include <memory>
#include <utility>

class IEntity
{
public:
	virtual ~IEntity() {}

	virtual int getID() const { return m_entityID; }
	virtual void setName(const std::string& name) { m_entityName = name; }
	virtual std::string getName() const { return m_entityName; }
	virtual void setActive(const bool& isActive) { m_isActive = isActive; }
	virtual bool isActive() const { return m_isActive; }
	virtual int getComponentCount() const { return m_entityComponents.size(); };
	virtual void setPosition(const Vector2& position) { m_entityPosition = position; }
	virtual const Vector2& getPosition() { return m_entityPosition; }

	virtual void sendEvent(const EEntityEvent& event) = 0;

protected:
	virtual void addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent) = 0;
	virtual IEntityComponent* getEntityComponentInternal(const std::string& componentName) = 0;

public:
	template <typename ComponentType>
	ComponentType* addEntityComponent(const std::string& componentName) 
	{ 
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>();
		component->initComponent(m_pSystem, this);
		this->addEntityComponentInternal(componentName, component);

		return component.get();
	}

	template <typename ComponentType>
	ComponentType* getEntityComponent(const std::string& componentName)
	{
		return static_cast<ComponentType*>(this->getEntityComponentInternal(componentName));
	}

protected:
	ISystem * m_pSystem = nullptr;
	int m_entityID = -1;
	std::string m_entityName = "";
	bool m_isActive = true;
	std::map<std::string, std::shared_ptr<IEntityComponent>> m_entityComponents{};
	Vector2 m_entityPosition{ 0.f, 0.f };
};