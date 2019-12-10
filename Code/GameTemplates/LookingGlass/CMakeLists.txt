cmake_minimum_required(VERSION 3.10)

project (Game VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB ROOT_SRC
	"StdAfx.h"
	"StdAfx.cpp"
	"Game.h"
	"Game.cpp"
)

file (GLOB PLAYER_SRC
	"Player/Player.h"
	"Player/Player.cpp"
)

include_directories("${SRC_DIR}/Common")
include_directories("${SRC_DIR}/Plugins")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC} ${PLAYER_SRC})

target_link_libraries(${PROJECT_NAME} Plugins)

source_group(" " FILES ${ROOT_SRC})
source_group("Player" FILES ${PLAYER_SRC})