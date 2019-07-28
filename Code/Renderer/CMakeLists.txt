cmake_minimum_required(VERSION 3.10)

project (Renderer VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "StdAfx.h"
  "StdAfx.cpp"
  "Renderer.h"
  "Renderer.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC})

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

