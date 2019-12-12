/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/EntitySystem/IEntityComponent.h>

class CWeapon : public IEntityComponent
{
public:
	CWeapon();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const EEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

private:
	void updateEvent();

private:
	int tempCounter;
};