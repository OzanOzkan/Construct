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
	CEntity(SEnvironment* env);
	virtual ~CEntity() {}
	
	// IEntity
	virtual void sendEvent(const EEntityEvent& event) override;
	// ~IEntity

protected:
	virtual void addEntityComponentInternal(const std::string& componentName, std::shared_ptr<IEntityComponent> entityComponent) override;
	virtual IEntityComponent* getEntityComponentInternal(const std::string& componentName) override;
};