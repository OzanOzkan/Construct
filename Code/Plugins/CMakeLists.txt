cmake_minimum_required(VERSION 3.10)

project (Plugins VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB ROOT_SRC
)

file(GLOB ENTITY_COMPONENTS
	"EntityComponents/SpriteRendererEntityComponent.h"
	"EntityComponents/SpriteRendererEntityComponent.cpp"
	"EntityComponents/TextRendererEntityComponent.h"
	"EntityComponents/TextRendererEntityComponent.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} STATIC ${ROOT_SRC} ${ENTITY_COMPONENTS})

source_group(" " FILES ${ROOT_SRC})
source_group("EntityComponents" FILES ${ENTITY_COMPONENTS})

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)