/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityBasicTypes.h>
#include <System/EntitySystem/IEntityComponent.h>

class CEntity : public IEntity
{
public:
	CEntity(ISystem* systemContext);
	
	// IEntity
	void sendEvent(const EEntityEvent& event) override;
	// ~IEntity

protected:
	void addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent) override;
	IEntityComponent* getEntityComponentInternal(const std::string& componentName) override;

private:
	ISystem * GetSystem() { return m_pSystem; }
};