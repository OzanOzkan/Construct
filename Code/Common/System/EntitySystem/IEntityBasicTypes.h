#pragma once

#include <string>

enum EEntityEvent
{
	ENTITY_EVENT_INIT = (1u << 0),
	ENTITY_EVENT_PREUPDATE = (1u << 1),
	ENTITY_EVENT_UPDATE = (1u << 2),
	ENTITY_EVENT_POSTUPDATE = (1u << 3),
	ENTITY_EVENT_DESTROY = (1u << 4),
	ENTITY_EVENT_TIMER_TICK = (1u << 5),
	ENTITY_EVENT_COLLISION = (1u << 6),
	ENTITY_LEVEL_LOAD_END = (1u << 7),
	ENTITY_COMPONENT_REMOVED = (1u << 8)
};

struct SEntityEvent
{
public:
	SEntityEvent(const EEntityEvent& event) noexcept
		: m_event(event)
		, m_data(nullptr)
	{}

	SEntityEvent(const EEntityEvent& event, void* data) noexcept
		: m_event(event)
		, m_data(data)
	{}

	const EEntityEvent& GetEvent() const noexcept { return m_event; }

	template <typename EventDataType>
	EventDataType* GetData() const { return static_cast<EventDataType*>(m_data); }

private:
	EEntityEvent m_event;
	void* m_data;
};