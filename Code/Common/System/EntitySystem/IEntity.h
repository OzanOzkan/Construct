#pragma once

#include "IEntitySystem.h"
#include "IEntityComponent.h"
#include "../../Math/Math.h"
#include "../../Utility/Utility.h"

#include <string>
#include <map>
#include <memory>
#include <utility>

class IEntity
{
public:
	virtual int					getID() const = 0;
	virtual void				setID(const int& entityId) = 0;
	virtual void				setName(const std::string& name) = 0;
	virtual std::string			getName() const = 0;
	virtual void				setActive(const bool& isActive) = 0;
	virtual bool				isActive() const = 0;
	virtual int					getComponentCount() const = 0;
	virtual void				setPosition(const Vector2& position) = 0;
	virtual const Vector2&		getPosition() = 0;
	virtual void				setRotation(const float& rotation) = 0;
	virtual float				getRotation() = 0;
	virtual void				setSize(const float& width, const float& height) = 0;
	virtual void				getSize(float& width, float& height) = 0;
	virtual void				setTag(const std::string& tag) = 0;
	virtual const std::string&	getTag() = 0;
	virtual void				sendEvent(const SEntityEvent& event) = 0;
	virtual void				setTimer(const float& seconds) = 0;

protected:
	virtual void							addEntityComponentInternal(const std::string& componentName, std::unique_ptr<IEntityComponent> entityComponent) = 0;
	virtual IEntityComponent*				getEntityComponentInternal(const std::string& componentName) = 0;
	virtual std::vector<IEntityComponent*>	getEntityComponentsInternal(const std::string& componentName) = 0;

public:
	template <typename ComponentType>
	ComponentType* addEntityComponent() 
	{ 
		return static_cast<ComponentType*>(findAndAddEntityComponent(Utility::getObjectName<ComponentType>()));
	}

	IEntityComponent* addEntityComponent(const std::string& componentName)
	{
		return findAndAddEntityComponent(componentName);
	}

	IEntityComponent* addEntityComponent(const std::string& componentName, IEntityComponent* component)
	{
		std::unique_ptr<IEntityComponent> comp = std::unique_ptr<IEntityComponent>(component);
		IEntityComponent* retVal = comp.get();

		comp->initComponent(m_pSystem, this);
		this->addEntityComponentInternal(componentName, std::move(comp));

		return retVal;
	}

	template <typename ComponentType>
	ComponentType* getEntityComponent()
	{
		return static_cast<ComponentType*>(this->getEntityComponentInternal(Utility::getObjectName<ComponentType>()));
	}

	template <typename ComponentType>
	std::vector<ComponentType*> getEntityComponents()
	{
		std::vector<ComponentType*> retVec{};

		for (auto component : getEntityComponentsInternal(Utility::getObjectName<ComponentType>()))
			retVec.push_back(static_cast<ComponentType*>(component));

		return retVec;
	}

private:
	IEntityComponent* findAndAddEntityComponent(const std::string& componentName)
	{
		IEntityComponent* retVal = nullptr;

		// Find requested component from component factory.
		if(IEntityComponent* pComponent = IEntitySystem::getEntityComponentFactory().Create(componentName))
		{
			// If requested component found.
			std::unique_ptr<IEntityComponent> component = std::unique_ptr<IEntityComponent>(pComponent);
			retVal = component.get();
			component->initComponent(m_pSystem, this);
			this->addEntityComponentInternal(componentName, std::move(component));
		}

		return retVal;
	}

protected:
	ISystem * m_pSystem = nullptr;
};