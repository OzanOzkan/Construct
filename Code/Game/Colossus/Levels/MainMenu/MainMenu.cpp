#include "MainMenu.h"

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityComponent.h>
#include <ILog.h>
#include <UI/UIButton.h>

#include "../LevelController.h"

#include <EntityComponents/AnimatedSpriteRendererEntityComponent.h>

/////////////////////////////////////////////////
CMainMenu::CMainMenu(ISystem* systemContext)
	: m_pSystem(systemContext)
{
}

/////////////////////////////////////////////////
void CMainMenu::loadLevel()
{
	// Load Level functions will be replaced with JSON level load system.

	constexpr int buttonWidth = 500;
	constexpr int buttonHeight = 150;
	constexpr int fontSize = 36;
	
	int resolutionW, resolutionH;
	GetSystem()->GetRenderer()->getResolution(resolutionW, resolutionH);

	SEntitySpawnParams uiParams;
	uiParams.entityName = "Canvas";
	IEntity* pUICanvas = GetSystem()->GetEntitySystem()->spawnEntity(uiParams);
	pUICanvas->setPosition(Vector2((resolutionW / 2) - (buttonWidth / 2), (resolutionH / 2) - (buttonHeight * 2.5)));

	UIButton* pUIButton = pUICanvas->addEntityComponent<UIButton>();
	pUIButton->setText("Nebula");
	pUIButton->setTextFontSize(fontSize);
	pUIButton->setSize(buttonWidth, buttonHeight);
	pUIButton->updateComponent();
	pUIButton->subscribeToPressEvent(
		[this, pUICanvas](const bool& isPressed, const Vector2 &selectionPos) {
		if (!isPressed) {
			GetSystem()->GetEntitySystem()->destroyEntity(pUICanvas->getID());
			CLevelController::getInstance(m_pSystem).loadLevel(ELevel::NEBULA);
		}
	});
	
	UIButton* pUIButton2 = pUICanvas->addEntityComponent<UIButton>();
	pUIButton2->setText("Isometrica");
	pUIButton2->setTextFontSize(fontSize);
	pUIButton2->setPosition(Vector2(0, (buttonHeight * 1) + 50));
	pUIButton2->setSize(buttonWidth, buttonHeight);
	pUIButton2->updateComponent();
	pUIButton2->subscribeToPressEvent(
		[this, pUICanvas](const bool& isPressed, const Vector2 &selectionPos) {
		if (!isPressed) {
			GetSystem()->GetEntitySystem()->destroyEntity(pUICanvas->getID());
			CLevelController::getInstance(m_pSystem).loadLevel(ELevel::ISOMETRICA);
		}
	});

	UIButton* pUIButton3 = pUICanvas->addEntityComponent<UIButton>();
	pUIButton3->setText("Physica");
	pUIButton3->setTextFontSize(fontSize);
	pUIButton3->setPosition(Vector2(0, (buttonHeight * 2) + 100));
	pUIButton3->setSize(buttonWidth, buttonHeight);
	pUIButton3->updateComponent();
	pUIButton3->subscribeToPressEvent(
		[this, pUICanvas](const bool& isPressed, const Vector2 &selectionPos) {
		if (!isPressed) {
			GetSystem()->GetEntitySystem()->destroyEntity(pUICanvas->getID());
			CLevelController::getInstance(m_pSystem).loadLevel(ELevel::PHYSICA);
		}
	});
}

/////////////////////////////////////////////////
void CMainMenu::onUpdate()
{
}
