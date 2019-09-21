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
)

add_custom_target(${PROJECT_NAME} SOURCES ${ROOT_SRC} ${SYSTEM_SRC})

source_group(" " FILES ${ROOT_SRC})
source_group("System" FILES ${SYSTEM_SRC})

#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION bin RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
