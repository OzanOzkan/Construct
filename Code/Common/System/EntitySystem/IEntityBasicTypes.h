/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <string>

enum EEntityEvent
{
	ENTITY_EVENT_INIT = (1u << 0),
	ENTITY_EVENT_UPDATE = (1u << 1)
};