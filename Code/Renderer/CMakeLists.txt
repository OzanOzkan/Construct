cmake_minimum_required(VERSION 3.10)

project (Renderer VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "StdAfx.h"
  "StdAfx.cpp"
  "Renderer.cpp"
)

file (GLOB SDL_RENDERER
	"SDLRenderer/SDLCamera.h"
	"SDLRenderer/SDLCamera.cpp"
	"SDLRenderer/SDLRenderer.h"
	"SDLRenderer/SDLRenderer.cpp"
	"SDLRenderer/SDLTexture.h"
	"SDLRenderer/SDLTexture.cpp"
	"SDLRenderer/SDLTextureManager.h"
	"SDLRenderer/SDLTextureManager.cpp"
)

file (GLOB RENDEREROBJECT
	"SDLRenderer/RendererObject/SDLRendererObject.h"
	"SDLRenderer/RendererObject/SDLRendererObject.cpp"
	"SDLRenderer/RendererObject/SDLSprite.h"
	"SDLRenderer/RendererObject/SDLSprite.cpp"
	"SDLRenderer/RendererObject/SDLText.h"
	"SDLRenderer/RendererObject/SDLText.cpp"
	"SDLRenderer/RendererObject/SDLRect.h"
	"SDLRenderer/RendererObject/SDLRect.cpp"
)
add_library (${PROJECT_NAME} SHARED ${ROOT_SRC} ${SDL_RENDERER} ${RENDEREROBJECT})

source_group("SDLRenderer" FILES ${SDL_RENDERER})
source_group("SDLRenderer\\RendererObject" FILES ${RENDEREROBJECT})

#find_package(OpenGL REQUIRED)
include_directories("${SRC_DIR}/Common")
#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

#include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/GL")
#include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glad/include")
#include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/stb_image/")

#include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glfw-3.3.bin.WIN64/include")
#link_directories("${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017")
#target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib")

#include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/freetype-2.10.1/include")
#link_directories("${SDK_DIR}/freetype-2.10.1/bin")
#target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/freetype-2.10.1/bin/freetype.lib")

#SDL2-2.0.10
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/SDL2-2.0.10/include")
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
link_directories("${SDK_DIR}/SDL2-2.0.10/lib/x64")
	target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/SDL2-2.0.10/lib/x64/SDL2.lib")
	target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/SDL2-2.0.10/lib/x64/SDL2_image.lib")
	target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/SDL2-2.0.10/lib/x64/SDL2_ttf.lib")
endif()

# Precompiled header
#set(PCH_FILE "$(IntDir)$(TargetName).pch")
#set(PrecompiledHeader "StdAfx.h")
#set(PrecompiledSource "StdAfx.cpp")
#set_source_files_properties("${PrecompiledSource}" PROPERTIES COMPILE_FLAGS " /Yc\"${PrecompiledHeader}\" /Fp\"${PCH_FILE}\" ")
#get_target_property(TARGET_SOURCES ${PROJECT_NAME} SOURCES)
#foreach(sourcefile ${TARGET_SOURCES})
#	if ("${sourcefile}" MATCHES ".*\\.\\cpp$")
#	  if (NOT "${sourcefile}" STREQUAL "${PrecompiledSource}")
#		set_property(SOURCE "${sourcefile}" APPEND_STRING PROPERTY COMPILE_FLAGS " /Yu\"${PrecompiledHeader}\" /Fp\"${PCH_FILE}\" ")
#	  endif()
#	endif()
#endforeach(sourcefile)

source_group(" " FILES ${ROOT_SRC})

#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION bin RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)