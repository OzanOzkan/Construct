#include "OnSelectionListenerEntityComponent.h"

#include <System/EntitySystem/IEntity.h>
#include <IInput.h>
#include <Renderer/IRenderer.h>
#include <ILog.h>

/////////////////////////////////////////////////
OnSelectionListenerEntityComponent::OnSelectionListenerEntityComponent()
	: m_lastSelectedPosition(Vector2(0,0))
	, m_isSelectedPreviousFrame(false)
	, m_debugDraw(false)
	, m_pBBDebugRect(nullptr)
	, m_pInputDebugRect(nullptr)
	, m_boundingBox()
{
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::Init()
{
	float width, height;
	getEntity()->getSize(width, height);
	m_boundingBox.w = width;
	m_boundingBox.h = height;

	updateBoundingBoxPosition();
}

/////////////////////////////////////////////////
unsigned int OnSelectionListenerEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_DESTROY;
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::onEvent(const SEntityEvent & event)
{
	if (event.GetEvent() == EEntityEvent::ENTITY_EVENT_UPDATE)
	{
		updateBoundingBoxPosition();
		processSelectionEvent();

		if (m_debugDraw)
			debugDraw();
	}
	else if (event.GetEvent() == EEntityEvent::ENTITY_EVENT_DESTROY)
	{
		if(m_pBBDebugRect) GetSystem()->GetRenderer()->RemoveRenderObject(m_pBBDebugRect);
		if(m_pInputDebugRect) GetSystem()->GetRenderer()->RemoveRenderObject(m_pInputDebugRect);
	}
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::processSelectionEvent()
{
	STouchEventList touchEvents = GetSystem()->GetInput()->GetTouchEvents();
	bool isMouseKeyPressed = GetSystem()->GetInput()->IsKeyPressed(EKey::eKID_MOUSE_LEFT);

	if (!touchEvents.empty() || isMouseKeyPressed)
	{
		Vector2 inputPosition = isMouseKeyPressed ? GetSystem()->GetInput()->GetMousePosition() 
			: touchEvents.front().position;

		if (checkSelection(inputPosition))
		{
			notifyListeners(true, inputPosition);
			m_isSelectedPreviousFrame = true;
			m_lastSelectedPosition = inputPosition;
		}
	}
	else
	{
		if (m_isSelectedPreviousFrame)
		{
			notifyListeners(false, m_lastSelectedPosition);
			m_isSelectedPreviousFrame = false;
			m_lastSelectedPosition = Vector2(0, 0);
		}
	}
}

/////////////////////////////////////////////////
bool OnSelectionListenerEntityComponent::checkSelection(const Vector2& positionToCheck)
{
	Math::Point selectionPoint;
	selectionPoint.x = positionToCheck.x;
	selectionPoint.y = positionToCheck.y;

	return Math::isPointInRect(selectionPoint, m_boundingBox);
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::notifyListeners(const bool & isSelected, const Vector2 & selectionPos)
{
	for (auto fn : m_callbacks)
		fn(isSelected, selectionPos);
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::updateComponent()
{
	updateBoundingBoxPosition();
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::subscribeOnSelection(TSelectionEventCallbackFn fn)
{
	m_callbacks.emplace_back(fn);
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::unsubscribeOnSelection(TSelectionEventCallbackFn fn)
{
	//auto elem = std::find(m_callbacks.begin(), m_callbacks.end(), fn);
	//m_callbacks.erase(elem);
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::setSize(const float& w, const float& h)
{
	m_boundingBox.w = w;
	m_boundingBox.h = h;
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::setDebugDraw(bool isActive)
{
	m_debugDraw = isActive;
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::updateBoundingBoxPosition()
{
	Vector2 entityPosition = getEntity()->getPosition();
	m_boundingBox.x = entityPosition.x + m_componentRelativePosition.x;
	m_boundingBox.y = entityPosition.y + m_componentRelativePosition.y;
}

/////////////////////////////////////////////////
void OnSelectionListenerEntityComponent::debugDraw()
{
	int layerId = 98;

	Vector2 boundingBoxPos;
	boundingBoxPos.x = m_boundingBox.x;
	boundingBoxPos.y = m_boundingBox.y;

	if (!m_pBBDebugRect)
	{
		SRectParams params;
		params.layerId = layerId;
		params.position = boundingBoxPos;
		params.height = m_boundingBox.h;
		params.width = m_boundingBox.w;

		m_pBBDebugRect = (IRect*)GetSystem()->GetRenderer()->CreateRenderObject(params);
		m_pBBDebugRect->setRenderActive(true);
	}
	else
	{
		m_pBBDebugRect->setPosition(boundingBoxPos);
	}

	if (!m_pInputDebugRect)
	{
		SRectParams params;
		params.layerId = layerId;
		params.position = GetSystem()->GetInput()->GetMousePosition();
		params.height = 10;
		params.width = 10;

		m_pInputDebugRect = (IRect*)GetSystem()->GetRenderer()->CreateRenderObject(params);
		m_pInputDebugRect->setRenderActive(true);
	}
	else
	{
		m_pInputDebugRect->setPosition(GetSystem()->GetInput()->GetMousePosition());
	}
}