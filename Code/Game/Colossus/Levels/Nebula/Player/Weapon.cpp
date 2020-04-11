/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Weapon.h"

#include <ILog.h>
#include <System/EntitySystem/IEntitySystem.h>
#include "Missile.h"

CWeapon::CWeapon()
	:tempCounter(0)
{
}

void CWeapon::Init()
{
}

unsigned int CWeapon::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

void CWeapon::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		updateEvent();
	}
	break;
	}
}

void CWeapon::updateComponent()
{
}

void CWeapon::updateEvent()
{
	++tempCounter;

	if (tempCounter > 5)
	{
		SEntitySpawnParams params;
		params.entityName = "Missile";
		params.position = getEntity()->getPosition() + getPosition();
		CMissile* pMissileEntity = GetSystem()->GetEntitySystem()->spawnEntity(params)->addEntityComponent<CMissile>();

		tempCounter = 0;
	}
}
