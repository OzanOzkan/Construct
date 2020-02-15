/* Copyright (C) 2020 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "EnvironmentController.h"


/////////////////////////////////////////////////
CEnvironmentController::CEnvironmentController()
{
}

/////////////////////////////////////////////////
void CEnvironmentController::Init()
{
	SpriteRendererEntityComponent* tile;

	tile = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	tile->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Isometric/house_01.png");
	tile->setPosition(Vector2(0,0));
	tile->updateComponent();
	m_tiles.push_back(tile);

	tile = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	tile->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Isometric/house_02.png");
	tile->setPosition(Vector2(800, 1200));
	tile->updateComponent();
	m_tiles.push_back(tile);

	tile = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	tile->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Isometric/house_03.png");
	tile->setPosition(Vector2(1600, 500));
	tile->updateComponent();
	m_tiles.push_back(tile);

	tile = getEntity()->addEntityComponent<SpriteRendererEntityComponent>();
	tile->setFile(GetSystem()->getFileManager()->getAssetsDirectory() + "Sprites/Isometric/house_04.png");
	tile->setPosition(Vector2(2400, 3800));
	tile->updateComponent();
	m_tiles.push_back(tile);
}

/////////////////////////////////////////////////
unsigned int CEnvironmentController::getEventMask() const
{
	return -1;
}

/////////////////////////////////////////////////
void CEnvironmentController::onEvent(const SEntityEvent & event)
{

}

/////////////////////////////////////////////////
void CEnvironmentController::updateComponent()
{

}