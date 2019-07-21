cmake_minimum_required(VERSION 3.10)

project (Renderer VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "StdAfx.h"
  "StdAfx.cpp"
  "Renderer.h"
  "Renderer.cpp"
)

file(GLOB WINDOW_SRC
  "Window/Window.h"
  "Window/Window.cpp"
)

file(GLOB VULKAN_SRC
  "Vulkan/Vulkan.h"
  "Vulkan/Vulkan.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC} ${WINDOW_SRC} ${VULKAN})

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
source_group("Window" FILES ${WINDOW_SRC})
source_group("Vulkan" FILES ${VULKAN_SRC})

#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION bin RUNTIME DESTINATION bin ARCHIVE DESTINATION lib)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

link_directories("${SDK_DIR}/VulkanSDK/1.1.108.0/Lib")
target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/VulkanSDK/1.1.108.0/Lib/vulkan-1.lib")
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/VulkanSDK/1.1.108.0/Include")

include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glm")

link_directories("${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017")
target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib")
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glfw-3.3.bin.WIN64/include")
