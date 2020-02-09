/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IEntityBasicTypes.h"
#include "../ISystem.h"
#include "../../Math/Math.h"

class IEntity;

class IEntityComponent
{
public:
	virtual ~IEntityComponent() {}

	virtual void Init() = 0;
	virtual unsigned int getEventMask() const = 0;
	virtual void onEvent(const SEntityEvent& event) = 0;
	virtual void updateComponent() = 0;
	
	IEntity* getEntity() { return m_pEntity; }
	void setActive(const bool& isActive) { m_isActive = isActive; }
	bool isActive() const { return m_isActive; }
	void setPosition(const Vector2& position) { m_componentRelativePosition = position; }
	const Vector2& getPosition() { return m_componentRelativePosition; }

protected:
	ISystem * GetSystem() { return m_pSystem; }

private:
	friend class IEntity;
	void initComponent(ISystem* systemContext, IEntity* pEntity) {
		m_pSystem = systemContext;
		m_pEntity = pEntity;
		Init();
	}

protected:
	ISystem * m_pSystem = nullptr;
	IEntity * m_pEntity = nullptr;
	bool m_isActive = true;
	Vector2 m_componentRelativePosition { 0,0 };
};