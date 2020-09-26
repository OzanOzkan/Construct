#include "B2DObject.h"

#include <Renderer/IRenderer.h>

#include <box2d/b2_fixture.h>
#include <box2d/b2_chain_shape.h>

/////////////////////////////////////////////////
CB2DObject::CB2DObject(ISystem* systemContext, IEntity* pEntity, const Vector2& bbox,
	const std::vector<Vector2>& vertices, const bool& isRotationLocked,
	const bool& isDynamic, b2Body* pB2Body)
	: m_pSystem(systemContext)
	, m_pEntity(pEntity)
	, m_bbox(bbox)
	, m_vertices(vertices)
	, m_isRotationLocked(isRotationLocked)
	, m_isDynamic(isDynamic)
	, m_pB2Body(pB2Body)
	, m_M2P(40)
	, m_P2M(1 / m_M2P)
	, m_isDebugDrawEnabled(false)
	, m_pDebugDrawRect(nullptr)
	, m_pDebugPolygon(nullptr)
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
		if (m_vertices.empty()) {
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
		else {
			if (!m_pDebugPolygon) {
				SPolygonParams params;
				params.layerId = 50;
				params.color = RGBAColor(0, 255, 0, 255);
				m_pDebugPolygon = static_cast<IPolygon*>(GetSystem()->GetRenderer()->CreateRenderObject(params));

				b2Vec2 pos = m_pB2Body->GetPosition();
				Vector2 pixpos = Vector2(pos.x * m_M2P, pos.y * m_M2P);

				//b2CircleShape* pshp = (b2CircleShape*)m_pB2Body->GetFixtureList()->GetShape();
				//for (int i = 0; i < m_vertices.size(); ++i) {
				//	m_pDebugPolygon->AddVertice(Vector2((pos.x * m_M2P) + (pshp->m_vertices[i].x * m_M2P), (pos.y * m_M2P) + (pshp->m_vertices[i].y * m_M2P)));
				//}

				for (Vector2 vertice : m_vertices) {
					m_pDebugPolygon->AddVertice(pixpos + vertice);
				}
			}
			else {
				// TODO: Set position of the debug polygon.
			}
		}
	}
	else if (m_pDebugDrawRect) {
		GetSystem()->GetRenderer()->RemoveRenderObject(m_pDebugDrawRect);
	}
	else if (m_pDebugPolygon) {
		GetSystem()->GetRenderer()->RemoveRenderObject(m_pDebugPolygon);
	}

}
