#pragma once

#include "IEntityBasicTypes.h"
#include "IEntitySystem.h"
#include "../ISystem.h"
#include "../../Math/Math.h"

class IEntityComponent
{
public:
	virtual void			Init() = 0;
	virtual unsigned int	getEventMask() const = 0;
	virtual void			onEvent(const SEntityEvent& event) = 0;
	virtual void			updateComponent() = 0;
	
	//virtual void getDescriptor(EntityComponentFactory::EntityComponentDescriptor& desc) {};
	
	IEntity*		getEntity() noexcept { return m_pEntity; }
	void			setActive(const bool& isActive) noexcept { m_isActive = isActive; }
	bool			isActive() const noexcept { return m_isActive; }
	void			setPosition(const Vector2& position) noexcept { m_componentRelativePosition = position; }
	const Vector2&	getPosition() noexcept { return m_componentRelativePosition; }
	void			setRotation(const float& rotation) noexcept { m_componentRotation = rotation; }
	float			getRotation() noexcept { return m_componentRotation; }

protected:
	ISystem * GetSystem() noexcept { return m_pSystem; }

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
	float m_componentRotation = 0;
};