#include "Nebula.h"

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>

#include "Player/PlayerShip.h"
#include "Environment/EnvironmentController.h"

#include <UI/UIButton.h>

/////////////////////////////////////////////////
CNebula::CNebula(ISystem* systemContext)
	: m_pSystem(systemContext)
{

}

/////////////////////////////////////////////////
void CNebula::loadLevel()
{
	SEntitySpawnParams environmentControllerSpawnParams;
	environmentControllerSpawnParams.entityName = "EnvironmentControllerEntity";
	GetSystem()->GetEntitySystem()->spawnEntity(environmentControllerSpawnParams)
		->addEntityComponent<CEnvironmentController>();


	SEntitySpawnParams playerSpawnParams;
	playerSpawnParams.entityName = "PlayerEntity";
	CPlayerShip* pPlayerShip = GetSystem()->GetEntitySystem()->spawnEntity(playerSpawnParams)
		->addEntityComponent<CPlayerShip>();


	auto windowSize = GetSystem()->GetWindowManager()->GetWindowSize();

	SEntitySpawnParams uiCanvas;
	uiCanvas.entityName = "UICanvas";
	IEntity* pUICanvas = GetSystem()->GetEntitySystem()->spawnEntity(uiCanvas);
	pUICanvas->setPosition(Vector2(windowSize.width - 350, windowSize.height - 200));

	UIButton* pButtonMoveRight = pUICanvas->addEntityComponent<UIButton>();
	pButtonMoveRight->setPosition(Vector2(165, 0));
	pButtonMoveRight->setSize(150, 150);
	pButtonMoveRight->setText("");
	pButtonMoveRight->setBackgroundImage(GetSystem()->getFileManager()->getAssetsDirectory() + "UI/arrow.png");
	pButtonMoveRight->updateComponent();
	pButtonMoveRight->subscribeToPressEvent([pPlayerShip](const bool& isPressed, const Vector2 &selectionPos) {
		if (isPressed)
		{
			pPlayerShip->getEntity()->setPosition(Vector2(pPlayerShip->getEntity()->getPosition().x + 10, pPlayerShip->getEntity()->getPosition().y));
		}
	});

	UIButton* pButtonMoveLeft = pUICanvas->addEntityComponent<UIButton>();
	pButtonMoveLeft->setSize(150, 150);
	pButtonMoveLeft->setText("");
	pButtonMoveLeft->setBackgroundImage(GetSystem()->getFileManager()->getAssetsDirectory() + "UI/arrow.png");
	pButtonMoveLeft->setRotation(180);
	pButtonMoveLeft->updateComponent();
	pButtonMoveLeft->subscribeToPressEvent([pPlayerShip](const bool& isPressed, const Vector2 &selectionPos) {
		if (isPressed)
		{
			pPlayerShip->getEntity()->setPosition(Vector2(pPlayerShip->getEntity()->getPosition().x - 10, pPlayerShip->getEntity()->getPosition().y));
		}
	});
}