/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IEntityComponent.h"

#include <string>
#include <memory>

class IEntity
{
public:
	virtual ~IEntity() {}

	virtual int getID() const = 0;
	virtual void setName(const std::string& name) = 0;
	virtual std::string getName() const = 0;
	virtual void setActive(const bool& isActive) = 0;
	virtual bool isActive() const = 0;
	virtual int getComponentCount() const = 0;

protected:
	virtual void addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent) = 0;
	virtual IEntityComponent* getEntityComponentInternal(const std::string& componentName) = 0;

public:
	template <typename ComponentType>
	ComponentType* createEntityComponent(const std::string& componentName) 
	{ 
		std::shared_ptr<ComponentType> component = std::make_shared<ComponentType>();
		this->addEntityComponentInternal(componentName, component);

		return component.get();
	}

	template <typename ComponentType>
	ComponentType* getEntityComponent(const std::string& componentName)
	{
		return static_cast<ComponentType*>(this->getEntityComponentInternal(componentName));
	}
};