cmake_minimum_required(VERSION 3.10)

project (Physics VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
  "Physics.cpp"
)

set(SDLPHYSICS_SRC
	"SDLPhysics/SDLPhysics.h"
	"SDLPhysics/SDLPhysics.cpp"
)

source_group(" " FILES ${ROOT_SRC})
source_group("SDLPhysics" FILES ${SDLPHYSICS_SRC})

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_library (${PROJECT_NAME} 
	SHARED 
		${ROOT_SRC} 
		${SDLPHYSICS_SRC}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		Common
		${SDL2_LIBRARIES}
)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)