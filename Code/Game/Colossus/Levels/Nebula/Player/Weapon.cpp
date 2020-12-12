#include "Weapon.h"

#include <System/EntitySystem/IEntity.h>
#include <ILog.h>
#include <System/EntitySystem/IEntitySystem.h>
#include "Missile.h"

CWeapon::CWeapon()
	: m_missleSpawnSpeed(0.1f)
{
}

void CWeapon::Init()
{
	getEntity()->setTimer(m_missleSpawnSpeed);
}

unsigned int CWeapon::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_TIMER_TICK;
}

void CWeapon::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_TIMER_TICK:
	{
		spawnMissile();
	}
	break;
	}
}

void CWeapon::updateComponent()
{
}

void CWeapon::spawnMissile()
{
	SEntitySpawnParams params;
	params.entityName = "Missile";
	params.position = getEntity()->getPosition() + getPosition();
	const CMissile* pMissileEntity = GetSystem()->GetEntitySystem()->spawnEntity(params)->addEntityComponent<CMissile>();
	getEntity()->setTimer(m_missleSpawnSpeed);
}
