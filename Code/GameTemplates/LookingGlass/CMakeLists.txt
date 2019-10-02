cmake_minimum_required(VERSION 3.10)

project (Game VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB ROOT_SRC
	"Game.h"
	"Game.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC})

source_group(" " FILES ${ROOT_SRC})