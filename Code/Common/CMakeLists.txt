cmake_minimum_required(VERSION 3.10)

project (Common VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "Core.h"
  "IRenderer.h"
  "IInput.h"
  "ILog.h"
  "IModule.h"
)

file(GLOB SYSTEM_SRC
	"System/ISystem.h"
	"System/IEventSystem.h"
	"System/IWindow.h"
	"System/IWindowEventListener.h"
	"System/IFileManager.h"
)

file(GLOB SYSTEM_ENTITY_SYSTEM_SRC
	"System/EntitySystem/IEntitySystem.h"
	"System/EntitySystem/IEntity.h"
	"System/EntitySystem/IEntityComponent.h"
	"System/EntitySystem/IEntityBasicTypes.h"
)

add_custom_target(${PROJECT_NAME} SOURCES ${ROOT_SRC} ${SYSTEM_SRC} ${SYSTEM_ENTITY_SYSTEM_SRC})

source_group(" " FILES ${ROOT_SRC})
source_group("System" FILES ${SYSTEM_SRC})
source_group("System\\EntitySystem" FILES ${SYSTEM_ENTITY_SYSTEM_SRC})

#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION bin RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
