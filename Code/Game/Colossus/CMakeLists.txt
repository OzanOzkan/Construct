cmake_minimum_required(VERSION 3.10)

project (Game VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(ROOT_SRC
	"Game.h"
	"Game.cpp"
)

set(LEVELS_SRC
	"Levels/ILevel.h"
	"Levels/LevelController.h"
	"Levels/LevelController.cpp"
)

set(MAINMENU_SRC
	"Levels/MainMenu/MainMenu.h"
	"Levels/MainMenu/MainMenu.cpp"
)

set(NEBULA_ROOT_SRC
	"Levels/Nebula/Nebula.h"
	"Levels/Nebula/Nebula.cpp"
	"Levels/Nebula/EnemyShip.h"
	"Levels/Nebula/EnemyShip.cpp"
)

set(NEBULA_PLAYER_SRC
	"Levels/Nebula/Player/PlayerShip.h"
	"Levels/Nebula/Player/PlayerShip.cpp"
	"Levels/Nebula/Player/Weapon.h"
	"Levels/Nebula/Player/Weapon.cpp"
	"Levels/Nebula/Player/Missile.h"
	"Levels/Nebula/Player/Missile.cpp"
)

set(NEBULA_ENVIRONMENT_SRC
	"Levels/Nebula/Environment/EnvironmentController.h"
	"Levels/Nebula/Environment/EnvironmentController.cpp"
	"Levels/Nebula/Environment/EnvironmentObject.h"
	"Levels/Nebula/Environment/EnvironmentObject.cpp"
	)

set(ISOMETRICA_ROOT_SRC
	"Levels/Isometrica/Isometrica.h"
	"Levels/Isometrica/Isometrica.cpp"
)

set(ISOMETRICA_PLAYER_SRC
	"Levels/Isometrica/Player/PlayerView.h"
	"Levels/Isometrica/Player/PlayerView.cpp"
)

set(ISOMETRICA_ENVIRONMENT_SRC
	"Levels/Isometrica/Environment/IsometricaEnvironmentController.h"
	"Levels/Isometrica/Environment/IsometricaEnvironmentController.cpp"
)

source_group(" " FILES ${ROOT_SRC})
source_group("UI" FILES ${UI_SRC})
source_group("Levels" FILES ${LEVELS_SRC})
source_group("Levels\\MainMenu" FILES ${MAINMENU_SRC})
source_group("Levels\\Nebula" FILES ${NEBULA_ROOT_SRC})
source_group("Levels\\Nebula\\Player" FILES ${NEBULA_PLAYER_SRC})
source_group("Levels\\Nebula\\Environment" FILES ${NEBULA_ENVIRONMENT_SRC})
source_group("Levels\\Isometrica" FILES ${ISOMETRICA_ROOT_SRC})
source_group("Levels\\Isometrica\\Player" FILES ${ISOMETRICA_PLAYER_SRC})
source_group("Levels\\Isometrica\\Environment" FILES ${ISOMETRICA_ENVIRONMENT_SRC})

include_directories("${SRC_DIR}/Plugins")

add_library (${PROJECT_NAME}
	SHARED
	${ROOT_SRC}
	${LEVELS_SRC}
	${MAINMENU_SRC}
	${NEBULA_ROOT_SRC}
	${NEBULA_PLAYER_SRC}
	${NEBULA_ENVIRONMENT_SRC}
	${ISOMETRICA_ROOT_SRC}
	${ISOMETRICA_PLAYER_SRC}
	${ISOMETRICA_ENVIRONMENT_SRC}
)

target_link_libraries(${PROJECT_NAME} PUBLIC Common Plugins)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)