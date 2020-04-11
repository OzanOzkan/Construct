cmake_minimum_required(VERSION 3.10)

project (System VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
	"StdAfx.h"
	"StdAfx.cpp"
	"Log.h"
	"Log.cpp"
	"System.h"
	"System.cpp"
	"FileManager.h"
	"FileManager.cpp"
)

set(EVENTSYSTEM
	"EventSystem/EventSystem.h"
	"EventSystem/EventSystem.cpp"
)

set(WINDOW
	"Window/WindowManager.h"
	"Window/WindowManager.cpp"
	"Window/Window.h"
	"Window/Window.cpp"
#	"Window/GLFWWindow.h"
#	"Window/GLFWWindow.cpp"
	"Window/SDLWindow.h"
	"Window/SDLWindow.cpp"
)

set(ENTITYSYSTEM
	"EntitySystem/EntitySystem.h"
	"EntitySystem/EntitySystem.cpp"
	"EntitySystem/Entity.h"
	"EntitySystem/Entity.cpp"
)

source_group(" " FILES ${ROOT_SRC})
source_group("EventSystem" FILES ${EVENTSYSTEM})
source_group("Window" FILES ${WINDOW})
source_group("EntitySystem" FILES ${ENTITYSYSTEM})

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_library (${PROJECT_NAME} 
	SHARED 
		${ROOT_SRC} 
		${EVENTSYSTEM} 
		${WINDOW} 
		${ENTITYSYSTEM}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		Common
		${SDL2_LIBRARIES}
)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)