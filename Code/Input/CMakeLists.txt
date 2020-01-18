cmake_minimum_required(VERSION 3.10)

project (Input VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "Input.cpp"
)

file(GLOB SDL_INPUT_SRC
	"SDLInput/SDLInput.h"
	"SDLInput/SDLInput.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC} ${SDL_INPUT_SRC})

source_group(" " FILES ${ROOT_SRC})
source_group("SDLInput" FILES ${SDL_INPUT_SRC})

#SDL2-2.0.10
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/SDL2-2.0.10/include")
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	link_directories("${SDK_DIR}/SDL2-2.0.10/lib/x64")
	target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/SDL2-2.0.10/lib/x64/SDL2.lib")
endif()

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)