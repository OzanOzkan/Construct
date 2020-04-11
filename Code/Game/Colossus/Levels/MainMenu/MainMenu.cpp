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
	SEntitySpawnParams uiParams;
	uiParams.entityName = "Canvas";
	IEntity* pUICanvas = GetSystem()->GetEntitySystem()->spawnEntity(uiParams);
	pUICanvas->setPosition(Vector2(100, 100));

	UIButton* pUIButton = pUICanvas->addEntityComponent<UIButton>();
	pUIButton->setText("Nebula");
	pUIButton->setSize(300, 100);
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
	pUIButton2->setPosition(Vector2(0, 150));
	pUIButton2->setSize(300, 100);
	pUIButton2->updateComponent();
	pUIButton2->subscribeToPressEvent(
		[this, pUICanvas](const bool& isPressed, const Vector2 &selectionPos) {
		if (!isPressed) {
			GetSystem()->GetEntitySystem()->destroyEntity(pUICanvas->getID());
			CLevelController::getInstance(m_pSystem).loadLevel(ELevel::ISOMETRICA);
		}
	});

	AnimatedSpriteRendererEntityComponent* pAnimatedSprite = pUICanvas->addEntityComponent<AnimatedSpriteRendererEntityComponent>();
	pAnimatedSprite->setPosition(Vector2(0, 500));
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame00.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame01.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame02.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame03.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame04.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame05.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame06.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame07.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame08.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame09.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame10.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame11.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame12.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame13.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame14.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame15.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame16.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame17.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame18.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame19.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame20.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame21.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame22.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame23.png");
	pAnimatedSprite->addFrameFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Animated/Explosion1/explosion1_frame24.png");
	pAnimatedSprite->updateComponent();
}
