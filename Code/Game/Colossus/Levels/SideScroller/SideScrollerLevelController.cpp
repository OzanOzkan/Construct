#include "SideScrollerLevelController.h"

#include <System/EntitySystem/IEntity.h>
#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
void CSideScrollerLevelController::Init()
{
}

/////////////////////////////////////////////////
unsigned int CSideScrollerLevelController::getEventMask() const
{
	return ENTITY_LEVEL_LOAD_END;
}

/////////////////////////////////////////////////
void CSideScrollerLevelController::onEvent(const SEntityEvent& event)
{
	if (event.GetEvent() == ENTITY_LEVEL_LOAD_END) {
		setupLevel();
	}
}

/////////////////////////////////////////////////
void CSideScrollerLevelController::updateComponent()
{
}

/////////////////////////////////////////////////
void CSideScrollerLevelController::setupLevel()
{
	if (IEntity* pGround = GetSystem()->GetEntitySystem()->findEntity("groundEntity")) {
		int resW, resH;
		GetSystem()->GetRenderer()->getResolution(resW, resH);

		pGround->setPosition(Vector2(0, resH - 250));
	}
}