cmake_minimum_required(VERSION 3.10)

project (Common VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
  "Core.h"
  "IInput.h"
  "ILog.h"
  "IModule.h"
  "IGame.h"
)

set(SYSTEM_SRC
	"System/ISystem.h"
	"System/IEventSystem.h"
	"System/IWindowManager.h"
	"System/IWindowEventListener.h"
	"System/IFileManager.h"
	"System/ITime.h"
)

set(SYSTEM_ENTITY_SYSTEM_SRC
	"System/EntitySystem/IEntitySystem.h"
	"System/EntitySystem/IEntity.h"
	"System/EntitySystem/IEntityComponent.h"
	"System/EntitySystem/IEntityBasicTypes.h"
)

set (SYSTEM_LEVEL_SYSTEM_SRC
	"System/LevelSystem/ILevelSystem.h"
)

set(RENDERER_SRC
	"Renderer/ICamera.h"
	"Renderer/IRenderer.h"
	"Renderer/IRenderObject.h"
	"Renderer/ITexture.h"
	"Renderer/ITextureManager.h"
)

set(MATH_SRC
	"Math/Math.h"
)

set(PHYSICS_SRC
	"Physics/IPhysics.h"
)

set (UTILITY_SRC
	"Utility/Utility.h"
	"Utility/Json.h"
)

source_group(" " FILES ${ROOT_SRC})
source_group("System" FILES ${SYSTEM_SRC})
source_group("System\\EntitySystem" FILES ${SYSTEM_ENTITY_SYSTEM_SRC})
source_group("System\\LevelSystem" FILES ${SYSTEM_LEVEL_SYSTEM_SRC})
source_group("Renderer" FILES ${RENDERER_SRC})
source_group("Math" FILES ${MATH_SRC})
source_group("Physics" FILES ${PHYSICS_SRC})
source_group("Utility" FILES ${UTILITY_SRC})

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}
)

# Hack for VS Solution Explorer
add_custom_target(${PROJECT_NAME}_
	SOURCES
		${ROOT_SRC}
		${SYSTEM_SRC}
		${SYSTEM_ENTITY_SYSTEM_SRC}
		${SYSTEM_LEVEL_SYSTEM_SRC}
		${SYSTEM_UI_SRC}
		${RENDERER_SRC}
		${MATH_SRC}
		${PHYSICS_SRC}
		${UTILITY_SRC}
)
