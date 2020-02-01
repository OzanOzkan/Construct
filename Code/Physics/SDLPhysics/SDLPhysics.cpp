#include "SDLPhysics.h"

/////////////////////////////////////////////////
CSDLPhysics::CSDLPhysics(ISystem* systemContext)
	: m_pSystem(systemContext)
{
}

/////////////////////////////////////////////////
void CSDLPhysics::InitializeModule()
{
}

/////////////////////////////////////////////////
void CSDLPhysics::onUpdate()
{
	ProcessCollisionCalculation();
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
				pEntityToCheckCollision->sendEvent(EEntityEvent::ENTITY_EVENT_COLLISION);
				pEntityToCheckCollisionWith->sendEvent(EEntityEvent::ENTITY_EVENT_COLLISION);
			}
		}
	}
}
