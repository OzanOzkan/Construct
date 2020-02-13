/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <string>

enum EEntityEvent
{
	ENTITY_EVENT_INIT = (1u << 0),
	ENTITY_EVENT_UPDATE = (1u << 1),
	ENTITY_EVENT_DESTROY = (1u << 2),
	ENTITY_EVENT_TIMER_TICK = (1u << 3),
	ENTITY_EVENT_COLLISION = (1u << 4)
};

struct SEntityEvent
{
public:
	SEntityEvent(const EEntityEvent& event)
		: m_event(event)
		, m_data(nullptr)
	{}

	SEntityEvent(const EEntityEvent& event, void* data)
		: m_event(event)
		, m_data(data)
	{}

	const EEntityEvent& GetEvent() const { return m_event; }

	template <typename EventDataType>
	EventDataType* GetData() const { return reinterpret_cast<EventDataType*>(m_data); }

private:
	EEntityEvent m_event;
	void* m_data;
};