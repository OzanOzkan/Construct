#include "SDLPhysics.h"

/////////////////////////////////////////////////
CSDLPhysics::CSDLPhysics(ISystem* systemContext)
	: m_pSystem(systemContext)
	, m_collisionListeners({})
	, m_physicalizedEntities({})
{
}

/////////////////////////////////////////////////
void CSDLPhysics::InitializeModule()
{
}

/////////////////////////////////////////////////
void CSDLPhysics::onUpdate()
{
	ProcessGravity();
	ProcessCollisionCalculation();
}

/////////////////////////////////////////////////
void CSDLPhysics::EnablePhysics2D(const S2DPhysicalizeParams & params)
{
	m_physicalizedEntities.emplace_back(params);
}

/////////////////////////////////////////////////
bool CSDLPhysics::AddCollisionListener(const SCollisionListenerParams& params)
{
	SDL_Rect rect;
	rect.w = params.w;
	rect.h = params.h;
	
	return m_collisionListeners.emplace(std::make_pair(params.pEntity, rect)).second;
}

/////////////////////////////////////////////////
void CSDLPhysics::RemoveCollisionListener(IEntity * pEntity)
{
	m_collisionListeners.erase(pEntity);
}

/////////////////////////////////////////////////
void CSDLPhysics::ProcessCollisionCalculation()
{
	for (auto entityToCheckCollisionPair : m_collisionListeners)
	{
		IEntity* pEntityToCheckCollision = entityToCheckCollisionPair.first;

		for (auto entityToCheckCollisionWithPair : m_collisionListeners)
		{
			IEntity* pEntityToCheckCollisionWith = entityToCheckCollisionWithPair.first;

			// If entities are the same do not calculate.
			if (pEntityToCheckCollision == pEntityToCheckCollisionWith)
				continue;

			// Calculate collision
			SDL_Rect entityToCheckCollisionRect;
			entityToCheckCollisionRect.x = pEntityToCheckCollision->getPosition().x;
			entityToCheckCollisionRect.y = pEntityToCheckCollision->getPosition().y;
			entityToCheckCollisionRect.w = entityToCheckCollisionPair.second.w;
			entityToCheckCollisionRect.h = entityToCheckCollisionPair.second.h;

			SDL_Rect entityToCheckCollisionWithRect;
			entityToCheckCollisionWithRect.x = pEntityToCheckCollisionWith->getPosition().x;
			entityToCheckCollisionWithRect.y = pEntityToCheckCollisionWith->getPosition().y;
			entityToCheckCollisionWithRect.w = entityToCheckCollisionWithPair.second.w;
			entityToCheckCollisionWithRect.h = entityToCheckCollisionWithPair.second.h;

			SDL_Rect collisionResultRect;
			if (SDL_IntersectRect(&entityToCheckCollisionRect, &entityToCheckCollisionWithRect, &collisionResultRect))
			{
				SPhysicsEventData data;
				data.pEntity1 = pEntityToCheckCollision;
				data.pEntity2 = pEntityToCheckCollisionWith;
				data.collisionPoint = Vector2(collisionResultRect.x, collisionResultRect.y);

				pEntityToCheckCollision->sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_COLLISION, &data });
				pEntityToCheckCollisionWith->sendEvent(SEntityEvent{ EEntityEvent::ENTITY_EVENT_COLLISION, &data });
			}
		}
	}
}

/////////////////////////////////////////////////
void CSDLPhysics::ProcessGravity()
{
	//for (auto params : m_physicalizedEntities)
	//{
	//	params.pEntity;
	//	params.mass;
	//}
}
