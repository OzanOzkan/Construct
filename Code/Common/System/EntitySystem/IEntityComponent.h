/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IEntityBasicTypes.h"
#include "../ISystem.h"

class IEntity;

class IEntityComponent
{
public:
	virtual ~IEntityComponent() {}

	virtual void Init() = 0;
	virtual IEntity* getEntity() { return m_pEntity; }
	virtual void setActive(const bool& isActive) { m_isActive = isActive; }
	virtual bool isActive() const { return m_isActive; }
	virtual unsigned int getEventMask() const = 0;
	virtual void onEvent(const EEntityEvent& event) = 0;
	virtual void updateComponent() = 0;

protected:
	ISystem * GetSystem() { return m_pSystem; }

private:
	friend class IEntity;
	virtual void initComponent(ISystem* systemContext, IEntity* pEntity) {
		m_pSystem = systemContext;
		m_pEntity = pEntity;
		Init();
	}

protected:
	ISystem * m_pSystem = nullptr;
	IEntity * m_pEntity = nullptr;
	bool m_isActive = true;
};