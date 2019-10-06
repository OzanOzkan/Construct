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

	virtual IEntity* getEntity() { return m_pEntity; }
	virtual void setActive(const bool& isActive) { m_isActive = isActive; }
	virtual bool isActive() const { return m_isActive; }
	virtual unsigned int getEventMask() const = 0;
	virtual void onEvent(const EEntityEvent& event) = 0;

protected:
	friend class IEntity;
	virtual void initComponent(SEnvironment* pEnv, IEntity* pEntity) { m_pEnv = pEnv; m_pEntity = pEntity; }

	SEnvironment * getEnvironment() { return m_pEnv; }

protected:
	SEnvironment * m_pEnv = nullptr;
	IEntity * m_pEntity = nullptr;
	bool m_isActive = true;
};