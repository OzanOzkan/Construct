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

	virtual int getID() const = 0;
	virtual void setID(const int& entityId) = 0;
	virtual void setName(const std::string& name) = 0;
	virtual std::string getName() const = 0;
	virtual void setActive(const bool& isActive) = 0;
	virtual bool isActive() const = 0;
	virtual int getComponentCount() const = 0;
	virtual void setPosition(const Vector2& position) = 0;
	virtual const Vector2& getPosition() = 0;

	virtual void sendEvent(const EEntityEvent& event) = 0;
	virtual void setTimer(const float& seconds) = 0;

protected:
	virtual void addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent) = 0;
	virtual IEntityComponent* getEntityComponentInternal(const std::string& componentName) = 0;
	virtual std::vector<IEntityComponent*> getEntityComponentsInternal(const std::string& componentName) = 0;

public:
	template <typename ComponentType>
	ComponentType* addEntityComponent() 
	{ 
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>();
		component->initComponent(m_pSystem, this);
		this->addEntityComponentInternal(typeid(ComponentType).name(), component);

		return component.get();
	}

	template <typename ComponentType>
	ComponentType* getEntityComponent()
	{
		return static_cast<ComponentType*>(this->getEntityComponentInternal(typeid(ComponentType).name()));
	}

	template <typename ComponentType>
	std::vector<ComponentType*> getEntityComponents()
	{
		std::vector<ComponentType*> retVec{};

		for (auto component : getEntityComponentsInternal(typeid(ComponentType).name()))
			retVec.push_back(static_cast<ComponentType*>(component));

		return retVec;
	}

protected:
	ISystem * m_pSystem = nullptr;
};