cmake_minimum_required(VERSION 3.10)

project (System VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB ROOT_SRC
	"StdAfx.h"
	"StdAfx.cpp"
	"Log.h"
	"Log.cpp"
	"System.h"
	"System.cpp"
	"FileManager.h"
	"FileManager.cpp"
)

file (GLOB EVENTSYSTEM
	"EventSystem/EventSystem.h"
	"EventSystem/EventSystem.cpp"
)

file (GLOB WINDOW
	"Window/WindowManager.h"
	"Window/WindowManager.cpp"
	"Window/Window.h"
	"Window/Window.cpp"
#	"Window/GLFWWindow.h"
#	"Window/GLFWWindow.cpp"
	"Window/SDLWindow.h"
	"Window/SDLWindow.cpp"
)

file (GLOB ENTITYSYSTEM
	"EntitySystem/EntitySystem.h"
	"EntitySystem/EntitySystem.cpp"
	"EntitySystem/Entity.h"
	"EntitySystem/Entity.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC} ${EVENTSYSTEM} ${WINDOW} ${ENTITYSYSTEM})

source_group(" " FILES ${ROOT_SRC})
source_group("EventSystem" FILES ${EVENTSYSTEM})
source_group("Window" FILES ${WINDOW})
source_group("EntitySystem" FILES ${ENTITYSYSTEM})

#include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glfw-3.3.bin.WIN64/include")
#link_directories("${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017")
#target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib")

#SDL2-2.0.10
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/SDL2-2.0.10/include")
link_directories("${SDK_DIR}/SDL2-2.0.10/lib/x64")
target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/SDL2-2.0.10/lib/x64/SDL2.lib")