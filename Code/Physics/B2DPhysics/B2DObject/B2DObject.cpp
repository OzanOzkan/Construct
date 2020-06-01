#include "B2DObject.h"

#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
CB2DObject::CB2DObject(ISystem* systemContext, IEntity* pEntity, const Vector2& bbox,
	const bool& isRotationLocked, const bool& isDynamic, b2Body* pB2Body)
	: m_pSystem(systemContext)
	, m_pEntity(pEntity)
	, m_bbox(bbox)
	, m_isRotationLocked(isRotationLocked)
	, m_isDynamic(isDynamic)
	, m_pB2Body(pB2Body)
	, m_M2P(40)
	, m_P2M(1 / m_M2P)
	, m_isDebugDrawEnabled(true)
	, m_pDebugDrawRect(nullptr)
{
}

/////////////////////////////////////////////////
void CB2DObject::PostPhysicsUpdate()
{
	DebugDraw();
}

/////////////////////////////////////////////////
Vector2 CB2DObject::GetVector2Position()
{
	b2Vec2 position = m_pB2Body->GetPosition();

	// Center point to top left and meters to pixels conversion.
	return Vector2((position.x * m_M2P) - m_bbox.x / 2, (position.y * m_M2P) - m_bbox.y / 2);
}

/////////////////////////////////////////////////
float CB2DObject::GetFRotation()
{
	float rotation = m_pB2Body->GetAngle();

	// Radians to degrees (Radians * 180 / PI)
	return rotation * 180 / 3.14;
}

/////////////////////////////////////////////////
void CB2DObject::DebugDraw()
{
	if (m_isDebugDrawEnabled) {
		if (!m_pDebugDrawRect) {
			SRectParams params;
			params.layerId = 50;
			params.width = m_bbox.x;
			params.height = m_bbox.y;
			params.color = RGBAColor(0, 255, 0, 255);
			params.renderObjectClass = ERenderObjectClass::WORLD;
			
			m_pDebugDrawRect = static_cast<IRect*>(GetSystem()->GetRenderer()->CreateRenderObject(params));
		}

		m_pDebugDrawRect->setPosition(GetVector2Position());
		m_pDebugDrawRect->setRotation(GetFRotation());
	}
	else if (m_pDebugDrawRect) {
		GetSystem()->GetRenderer()->RemoveRenderObject(m_pDebugDrawRect);
	}
}
