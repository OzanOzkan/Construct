cmake_minimum_required(VERSION 3.10)

project (Plugins VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
)

set(ENTITY_COMPONENTS
	"EntityComponents/CollisionEntityComponent.h"
	"EntityComponents/CollisionEntityComponent.cpp"
	"EntityComponents/AnimatedSpriteRendererEntityComponent.h"
	"EntityComponents/AnimatedSpriteRendererEntityComponent.cpp"
	"EntityComponents/SpriteRendererEntityComponent.h"
	"EntityComponents/SpriteRendererEntityComponent.cpp"
	"EntityComponents/TextRendererEntityComponent.h"
	"EntityComponents/TextRendererEntityComponent.cpp"
	"EntityComponents/OnSelectionListenerEntityComponent.h"
	"EntityComponents/OnSelectionListenerEntityComponent.cpp"
)

set (PHYSICS
	"EntityComponents/Physics/Rigidbody2D.h"
	"EntityComponents/Physics/Rigidbody2D.cpp"
)

set(UI
	"UI/UIButton.h"
	"UI/UIButton.cpp"
)

add_library (${PROJECT_NAME} 
	STATIC 
		${ROOT_SRC} 
		${ENTITY_COMPONENTS} 
		${UI} 
		${PHYSICS}
)

source_group(" " FILES ${ROOT_SRC})
source_group("EntityComponents" FILES ${ENTITY_COMPONENTS})
source_group("EntityComponents\\Physics" FILES ${PHYSICS})
source_group("UI" FILES ${UI})

target_link_libraries(${PROJECT_NAME} PUBLIC Common)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)