cmake_minimum_required(VERSION 3.10)

project (Renderer VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "StdAfx.h"
  "StdAfx.cpp"
  "Renderer.h"
  "Renderer.cpp"
  "Shader.h"
  "Shader.cpp"
  "glad.cpp"
)

file (GLOB TEXTRENDERER
  "TextRenderer/TextRenderer.h"
  "TextRenderer/TextRenderer.cpp"
)

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC} ${TEXTRENDERER})

source_group("TextRenderer" FILES ${TEXTRENDERER})

find_package(OpenGL REQUIRED)
include_directories("${SRC_DIR}/Common" ${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glm")
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/GL")
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glad/include")

include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glfw-3.3.bin.WIN64/include")
link_directories("${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017")
target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib")

include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/freetype-2.10.1/include")
link_directories("${SDK_DIR}/freetype-2.10.1/bin")
target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/freetype-2.10.1/bin/freetype.lib")


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