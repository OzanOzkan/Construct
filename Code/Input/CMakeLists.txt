cmake_minimum_required(VERSION 3.10)

project (Input VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
  "Input.cpp"
)

set(SDL_INPUT_SRC
	"SDLInput/SDLInput.h"
	"SDLInput/SDLInput.cpp"
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library (${PROJECT_NAME} 
	SHARED 
		${ROOT_SRC} 
		${SDL_INPUT_SRC}
)

source_group(" " FILES ${ROOT_SRC})
source_group("SDLInput" FILES ${SDL_INPUT_SRC})

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		Common 
		${SDL2_LIBRARIES}
)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)