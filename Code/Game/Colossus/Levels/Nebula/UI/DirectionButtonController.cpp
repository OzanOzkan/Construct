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
	return 0;
}

/////////////////////////////////////////////////
void CDirectionButtonController::onEvent(const SEntityEvent& event)
{
}

/////////////////////////////////////////////////
void CDirectionButtonController::updateComponent()
{
}

/////////////////////////////////////////////////
void CDirectionButtonController::setupButton()
{
	int resolutionW, resolutionH;
	GetSystem()->GetRenderer()->getResolution(resolutionW, resolutionH);
	getEntity()->setPosition(Vector2(resolutionW - 350, resolutionH - 200));

	if (IEntity* pPlayerEntity = GetSystem()->GetEntitySystem()->findEntity("playerEntity")) {
		auto buttons = getEntity()->getEntityComponents<UIButton>();
		for (auto button : buttons) {
			if (button->getComponentTag().compare("btnRight") == 0) {
				button->subscribeToPressEvent([pPlayerEntity](const bool& isPressed, const Vector2& selectionPos) {
					Vector2 currentPlayerPos = pPlayerEntity->getPosition();
					pPlayerEntity->setPosition(currentPlayerPos + Vector2(10, 0));
				});
			}
			else if (button->getComponentTag().compare("btnLeft") == 0) {
				button->subscribeToPressEvent([pPlayerEntity](const bool& isPressed, const Vector2& selectionPos) {
					Vector2 currentPlayerPos = pPlayerEntity->getPosition();
					pPlayerEntity->setPosition(currentPlayerPos - Vector2(10, 0));
				});
			}
		}
	}
}