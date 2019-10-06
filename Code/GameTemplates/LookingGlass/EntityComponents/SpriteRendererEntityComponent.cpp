#include "SpriteRendererEntityComponent.h"

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityBasicTypes.h>
#include <IRenderer.h>
#include <ILog.h>

/////////////////////////////////////////////////
unsigned int SpriteRendererEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEvent(const EEntityEvent & event)
{
	switch (event)
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		onEntityUpdate();
	}
	break;
	}
}

/////////////////////////////////////////////////
void SpriteRendererEntityComponent::onEntityUpdate()
{
	getEnvironment()->pLog->Log("SpriteRendererEntityComponent::onEntityUpdate()");
}