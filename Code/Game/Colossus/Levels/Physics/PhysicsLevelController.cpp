#include "PhysicsLevelController.h"

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>
#include <Renderer/IRenderer.h>
#include <EntityComponents/SpriteRendererEntityComponent.h>
#include <EntityComponents/AnimatedSpriteRendererEntityComponent.h>
#include <EntityComponents/CollisionEntityComponent.h>
#include <EntityComponents/Physics/Rigidbody2D.h>
#include <EntityComponents/OnSelectionListenerEntityComponent.h>

/////////////////////////////////////////////////
void CPhysicsLevelController::Init()
{

}

/////////////////////////////////////////////////
unsigned int CPhysicsLevelController::getEventMask() const
{
	return ENTITY_EVENT_UPDATE | ENTITY_LEVEL_LOAD_END;
}

/////////////////////////////////////////////////
void CPhysicsLevelController::onEvent(const SEntityEvent& event)
{
	if (event.GetEvent() == ENTITY_EVENT_UPDATE) {
		physicalizedObjectSpawner();
	}
	else if (event.GetEvent() == ENTITY_LEVEL_LOAD_END) {
		setupLevel();
	}
}

/////////////////////////////////////////////////
void CPhysicsLevelController::updateComponent()
{
}

/////////////////////////////////////////////////
void CPhysicsLevelController::setupLevel()
{
	if (IEntity* pGround = GetSystem()->GetEntitySystem()->findEntity("groundEntity")) {
		int resW, resH;
		GetSystem()->GetRenderer()->getResolution(resW, resH);

		pGround->setPosition(Vector2(0, resH - 250));
	}
}

void CPhysicsLevelController::physicalizedObjectSpawner()
{
	static int spawnTime = 0;

	if (spawnTime >= 100)
	{
		// Physicalized Object
		SEntitySpawnParams physicalizedObjectParams;
		physicalizedObjectParams.entityName = "physicalizedObject";
		physicalizedObjectParams.position = Vector2(110, 50);
		IEntity* pPhysicalizedObjectEntity = GetSystem()->GetEntitySystem()->spawnEntity(physicalizedObjectParams);

		SpriteRendererEntityComponent* pPhysicalizedObjectSprite = pPhysicalizedObjectEntity->addEntityComponent<SpriteRendererEntityComponent>();
		pPhysicalizedObjectSprite->setFile("Sprites/tntbox.png");
		pPhysicalizedObjectSprite->setLayerId(10);
		pPhysicalizedObjectSprite->updateComponent();

		float hObject, wObject;
		pPhysicalizedObjectSprite->getSize(hObject, wObject);

		CollisionEntityComponent* pPhysicalizedObjectCollider = pPhysicalizedObjectEntity->addEntityComponent<CollisionEntityComponent>();
		pPhysicalizedObjectCollider->SetSize(wObject, hObject);
		pPhysicalizedObjectCollider->updateComponent();
		//pPhysicalizedObjectCollider->setDebugDraw(true);

		Rigidbody2D* pPhysicalizedObjectRigidbody = pPhysicalizedObjectEntity->addEntityComponent<Rigidbody2D>();

		OnSelectionListenerEntityComponent* pPhysicalizedObjectSelection = pPhysicalizedObjectEntity->addEntityComponent<OnSelectionListenerEntityComponent>();
		pPhysicalizedObjectSelection->setSize(wObject, hObject);
		pPhysicalizedObjectSelection->updateComponent();
		pPhysicalizedObjectSelection->subscribeOnSelection([this, pPhysicalizedObjectEntity](const bool& isSelected, const Vector2& selectionPos) {
			if (isSelected) {
				GetSystem()->GetEntitySystem()->destroyEntity(pPhysicalizedObjectEntity->getID());

				SEntitySpawnParams explosionParams;
				explosionParams.entityName = "Explosion";
				explosionParams.position = pPhysicalizedObjectEntity->getPosition();
				IEntity* pExplosion = GetSystem()->GetEntitySystem()->spawnEntity(explosionParams);
				AnimatedSpriteRendererEntityComponent* pPhysicalizedObjectAnimatedSprite = pExplosion->addEntityComponent<AnimatedSpriteRendererEntityComponent>();
				pPhysicalizedObjectAnimatedSprite->setPosition(Vector2(-100, -100));
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame00.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame01.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame02.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame03.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame04.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame05.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame06.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame07.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame08.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame09.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame10.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame11.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame12.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame13.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame14.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame15.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame16.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame17.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame18.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame19.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame20.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame21.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame22.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame23.png");
				pPhysicalizedObjectAnimatedSprite->addFrameFile("Sprites/Animated/Explosion1/explosion1_frame24.png");
				pPhysicalizedObjectAnimatedSprite->updateComponent();
				pPhysicalizedObjectAnimatedSprite->subscribeToAnimationLoop([this, pExplosion](const int& currentFrame, const int& frameCount) {
					if (currentFrame == frameCount)
					{
						GetSystem()->GetEntitySystem()->destroyEntity(pExplosion->getID());
					}
					});
			}
			});
		// ~Physicalized Object

		spawnTime = 0;
	}

	spawnTime++;
}
