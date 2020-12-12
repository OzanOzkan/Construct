cmake_minimum_required(VERSION 3.10)

project (System VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
	"StdAfx.h"
	"StdAfx.cpp"
	"System.h"
	"System.cpp"
	"Log.h"
	"Log.cpp"
	"Time.h"
	"Time.cpp"
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
	"EntitySystem/EntityComponentFactory.h"
	"EntitySystem/EntityComponentFactory.cpp"
	"EntitySystem/Entity.h"
	"EntitySystem/Entity.cpp"
)

set(FILESYSTEM
	"FileSystem/FileManager.h"
	"FileSystem/FileManager.cpp"
	"FileSystem/SDLFileOps.h"
	"FileSystem/SDLFileOps.cpp"
)

set(LEVELSYSTEM
	"LevelSystem/LevelSystem.h"
	"LevelSystem/LevelSystem.cpp"
)

source_group(" " FILES ${ROOT_SRC})
source_group("Window" FILES ${WINDOW})
source_group("EntitySystem" FILES ${ENTITYSYSTEM})
source_group("FileSystem" FILES ${FILESYSTEM})
source_group("LevelSystem" FILES ${LEVELSYSTEM})

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDK_DIR})

add_library (${PROJECT_NAME} 
	SHARED 
		${ROOT_SRC} 
		${WINDOW} 
		${ENTITYSYSTEM}
		${FILESYSTEM}
		${LEVELSYSTEM}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		Common
		${SDL2_LIBRARIES}
)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)