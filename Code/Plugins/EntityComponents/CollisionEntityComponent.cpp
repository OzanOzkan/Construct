#include "CollisionEntityComponent.h"

#include <Physics/IPhysics.h>
#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
CollisionEntityComponent::CollisionEntityComponent()
	: m_pDebugRect(nullptr)
	, m_width(-1)
	, m_height(-1)
{
}

/////////////////////////////////////////////////
void CollisionEntityComponent::Init()
{
	SCollisionListenerParams params;
	params.pEntity = getEntity();

	GetSystem()->GetPhysics()->AddCollisionListener(params);
}

/////////////////////////////////////////////////
unsigned int CollisionEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_COLLISION | EEntityEvent::ENTITY_EVENT_DESTROY;
}

/////////////////////////////////////////////////
void CollisionEntityComponent::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		//DebugDraw();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_DESTROY:
	{
		onEntityDestroyEvent();
	}
	break;
	}
}

/////////////////////////////////////////////////
void CollisionEntityComponent::updateComponent()
{
	GetSystem()->GetPhysics()->RemoveCollisionListener(getEntity());

	SCollisionListenerParams params;
	params.pEntity = getEntity();
	params.w = m_width;
	params.h = m_height;

	GetSystem()->GetPhysics()->AddCollisionListener(params);

	if (m_pDebugRect)
		GetSystem()->GetRenderer()->RemoveRenderObject(m_pDebugRect);
}

/////////////////////////////////////////////////
void CollisionEntityComponent::SetSize(const int & w, const int & h)
{
	m_width = w;
	m_height = h;
}

/////////////////////////////////////////////////
void CollisionEntityComponent::onEntityDestroyEvent()
{
	GetSystem()->GetPhysics()->RemoveCollisionListener(getEntity());

	if (m_pDebugRect)
		GetSystem()->GetRenderer()->RemoveRenderObject(m_pDebugRect);
}

/////////////////////////////////////////////////
void CollisionEntityComponent::DebugDraw()
{
	int layerId = 98;

	// Bounding box
	if (!m_pDebugRect)
	{
		SRectParams params;
		params.layerId = layerId;
		params.position = getEntity()->getPosition() + getPosition();
		params.height = m_height;
		params.width = m_width;

		m_pDebugRect = (IRect*)GetSystem()->GetRenderer()->CreateRenderObject(params);
		m_pDebugRect->setRenderActive(true);
	}
	else
	{
		m_pDebugRect->setPosition(getEntity()->getPosition() + getPosition());
	}
}
