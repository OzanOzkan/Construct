#include "MainMenuButtonController.h"

#include <System/EntitySystem/IEntity.h>
#include <System/LevelSystem/ILevelSystem.h>
#include <UI/UIButton.h>

/////////////////////////////////////////////////
void MainMenuButtonController::Init()
{
	if (UIButton* pUIButton = getEntity()->getEntityComponent<UIButton>()) {
		pUIButton->subscribeToPressEvent([this](const bool& isPressed, const Vector2& selectionPos) {
			if (!isPressed) {
				GetSystem()->GetLevelSystem()->loadLevel(m_levelToLoad);
			}
		});
	}
}
