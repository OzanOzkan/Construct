#include "LevelSystem.h"

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>
#include <System/IFileManager.h>
#include <Utility/Json.h>
#include <ILog.h>

#include <map>

#include <iostream>

/////////////////////////////////////////////////
CLevelSystem::CLevelSystem(ISystem* systemContext)
	: m_pSystem(systemContext)
	, m_currentLevelName("")
{
}

/////////////////////////////////////////////////
void CLevelSystem::loadLevel(const std::string& levelName)
{
	getSystem()->GetLogger()->Log(("Loading level: " + levelName).c_str());

	unloadLevel();

	const std::string levelFileRawContent = getSystem()->getFileManager()->readFile(
		getSystem()->getFileManager()->getAssetsDirectory() + "Levels/" + levelName + ".lvl");
	
	if (levelFileRawContent.empty()) {
		getSystem()->GetLogger()->Log("Level not found.");
		return;
	}

	try {
		json levelFileJsonContent = json::parse(levelFileRawContent);

		json jsonEntityList = levelFileJsonContent["entityList"];
		for (json jsonEntity : jsonEntityList) {
			SEntitySpawnParams entitySpawnParams;
			entitySpawnParams.entityName = jsonEntity["name"].get<std::string>();
			entitySpawnParams.position = Vector2(jsonEntity["position"]["x"].get<float>(), jsonEntity["position"]["y"].get<float>());
			entitySpawnParams.width = jsonEntity["size"]["width"].get<float>();
			entitySpawnParams.height = jsonEntity["size"]["height"].get<float>();

			IEntity* pSpawnedEntity = getSystem()->GetEntitySystem()->spawnEntity(entitySpawnParams);
			pSpawnedEntity->setTag(jsonEntity["tag"].get<std::string>());

			json jsonComponentList = jsonEntity["components"];
			for (json jsonComponent : jsonComponentList) {
				std::string componentType = jsonComponent["componentType"].get<std::string>();
				IEntityComponent* pEntityComponent = IEntitySystem::getEntityComponentFactory().Create(componentType);
				pSpawnedEntity->addEntityComponent(componentType, pEntityComponent);

				pEntityComponent->setActive(jsonComponent["isActive"].get<bool>());
				pEntityComponent->setPosition(Vector2(jsonComponent["position"]["x"].get<float>(), jsonComponent["position"]["y"].get<float>()));
				pEntityComponent->setRotation(jsonComponent["rotation"].get<float>());
				pEntityComponent->setComponentTag(jsonComponent["tag"].get<std::string>());

				std::map<std::string, void*> desc;
				pEntityComponent->getClassDesc(desc);
				json jsonComponentProperties = jsonComponent["componentProperties"];
				for (json::iterator it = jsonComponentProperties.begin(); it != jsonComponentProperties.end(); ++it) {
					auto componentProperty = desc.find(it.key());
					if (componentProperty != desc.end()) {
						if (it.value().is_number()) {
							if (it.value().is_number_integer()) {
								*((int*)componentProperty->second) = it.value().get<int>();
							}
							else if (it.value().is_number_float()) {
								*((float*)componentProperty->second) = it.value().get<float>();
							}
						}
						else if (it.value().is_boolean()) {
							*((bool*)componentProperty->second) = it.value().get<bool>();
						}
						else if (it.value().is_string()) {
							*((std::string*)componentProperty->second) = it.value().get<std::string>();
						}
						else if (it.value().is_object()) {
							// TODO: Handle nested JSON objects.
							// TODO: Handle class/struct data types.
							// TODO: Handle user defined data types.
						}
					}
				}
				pEntityComponent->updateComponent();
			}
		}

		m_currentLevelName = levelName;

		publishLevelLoadEvent();

		getSystem()->GetLogger()->Log("Level loaded.");
	}
	catch (json::exception& e) {
		m_currentLevelName = "";

		getSystem()->GetLogger()->Log("Level load failed.");
		getSystem()->GetLogger()->Log(e.what());
	}
}

/////////////////////////////////////////////////
void CLevelSystem::unloadLevel()
{
	auto entityList = getSystem()->GetEntitySystem()->getEntities();
	for (auto entity : entityList)
	{
		getSystem()->GetEntitySystem()->destroyEntity(entity->getID());
	}
}

/////////////////////////////////////////////////
void CLevelSystem::resetLevel()
{
	unloadLevel();
	loadLevel(m_currentLevelName);
}

/////////////////////////////////////////////////
std::string CLevelSystem::getCurrentLevelName()
{
	return m_currentLevelName;
}

/////////////////////////////////////////////////
void CLevelSystem::publishLevelLoadEvent()
{
	auto entityList = getSystem()->GetEntitySystem()->getEntities();
	for (auto entity : entityList)
	{
		entity->sendEvent(ENTITY_LEVEL_LOAD_END);
	}
}
