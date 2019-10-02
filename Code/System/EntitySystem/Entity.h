#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityComponent.h>

#include <string>
#include <map>

class CEntity : public IEntity
{
public:
	virtual ~CEntity() {}
	
	virtual int getID() const override { return m_entityID; }
	virtual std::string getName() const override { return m_entityName; }
	virtual bool isActive() const override { return m_isActive; };
	virtual void setActive(const bool& isActive) override { m_isActive = isActive; }
	//virtual void addEntityComponent(const std::string& componentName, IEntityComponent entityComponent) override;
	virtual IEntityComponent* getEntityComponent(const std::string& componentName) override;

private:
	int m_entityID;
	std::string m_entityName{};
	bool m_isActive = true;
	std::map<std::string, IEntityComponent*> m_entityComponents{};
};