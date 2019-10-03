/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityComponent.h>

#include <string>
#include <map>
#include <memory>

class CEntity : public IEntity
{
public:
	virtual ~CEntity() {}
	
	virtual int getID() const override { return m_entityID; }
	virtual void setName(const std::string& name) { m_entityName = name; }
	virtual std::string getName() const override { return m_entityName; }
	virtual bool isActive() const override { return m_isActive; };
	virtual void setActive(const bool& isActive) override { m_isActive = isActive; }
	virtual void addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent) override;
	virtual IEntityComponent* getEntityComponentInternal(const std::string& componentName) override;
	virtual int getComponentCount() const override { return m_entityComponents.size(); }

private:
	int m_entityID;
	std::string m_entityName = "";
	bool m_isActive = true;
	std::map<std::string, std::shared_ptr<IEntityComponent>> m_entityComponents{};
};