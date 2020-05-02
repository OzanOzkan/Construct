#include "Isometrica.h"

#include <System/ISystem.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>

#include "Player/PlayerView.h"
#include "Environment/IsometricaEnvironmentController.h"

#include <EntityComponents/TextRendererEntityComponent.h>

/////////////////////////////////////////////////
CIsometrica::CIsometrica(ISystem* systemContext)
	: m_pSystem(systemContext)
{

}

/////////////////////////////////////////////////
void CIsometrica::loadLevel()
{
	SEntitySpawnParams params;

	params.entityName = "Player";
	GetSystem()->GetEntitySystem()->spawnEntity(params)->addEntityComponent<CPlayerView>();

	params.entityName = "EnvironmentController";
	GetSystem()->GetEntitySystem()->spawnEntity(params)->addEntityComponent<CIsometricaEnvironmentController>();
}

/////////////////////////////////////////////////
void CIsometrica::onUpdate()
{
}
