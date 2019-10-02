#pragma once

#include "IEntityComponent.h"
#include <string>

class IEntity
{
public:
	virtual ~IEntity() {}

	virtual int getID() const = 0;
	virtual std::string getName() const = 0;
	virtual void setActive(const bool& isActive) = 0;
	virtual bool isActive() const = 0;
	//virtual void addEntityComponent(const std::string& componentName, IEntityComponent entityComponent) = 0;
	virtual IEntityComponent* getEntityComponent(const std::string& componentName) = 0;
};