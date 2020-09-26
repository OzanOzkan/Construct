#include "DirectionButtonController.h"

#include <System/EntitySystem/IEntity.h>
#include <UI/UIButton.h>

/////////////////////////////////////////////////
void CDirectionButtonController::Init()
{
	setupButton();
}

/////////////////////////////////////////////////
unsigned int CDirectionButtonController::getEventMask() const
{
	return ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void CDirectionButtonController::onEvent(const SEntityEvent& event)
{
	int resolutionW, resolutionH;
	GetSystem()->GetRenderer()->getResolution(resolutionW, resolutionH);
	getEntity()->setPosition(Vector2(resolutionW - 350, resolutionH - 200));
}

/////////////////////////////////////////////////
void CDirectionButtonController::updateComponent()
{
}

/////////////////////////////////////////////////
void CDirectionButtonController::setupButton()
{
	if (IEntity* pPlayerEntity = GetSystem()->GetEntitySystem()->findEntity("playerEntity")) {
		auto buttons = getEntity()->getEntityComponents<UIButton>();
		for (auto button : buttons) {
			if (button->getComponentTag().compare("btnRight") == 0) {
				button->subscribeToPressEvent([pPlayerEntity, this](const bool& isPressed, const Vector2& selectionPos) {
					Vector2 currentPlayerPos = pPlayerEntity->getPosition();
					pPlayerEntity->setPosition(currentPlayerPos + (Vector2(800, 0) * GetSystem()->GetTime()->GetDeltaTime()));
				});
			}
			else if (button->getComponentTag().compare("btnLeft") == 0) {
				button->subscribeToPressEvent([pPlayerEntity, this](const bool& isPressed, const Vector2& selectionPos) {
					Vector2 currentPlayerPos = pPlayerEntity->getPosition();
					pPlayerEntity->setPosition(currentPlayerPos - Vector2(800, 0) * GetSystem()->GetTime()->GetDeltaTime());
				});
			}
		}
	}
}