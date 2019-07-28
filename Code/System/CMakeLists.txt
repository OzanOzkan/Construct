cmake_minimum_required(VERSION 3.10)

project (System VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB ROOT_SRC
  "Log.h"
  "Log.cpp"
  "System.h"
  "System.cpp"
)

file (GLOB EVENTSYSTEM
  "EventSystem/EventSystem.h"
  "EventSystem/EventSystem.cpp"
)

file (GLOB WINDOW
	"Window/WindowManager.h"
	"Window/WindowManager.cpp"
	"Window/GLFWWindow.h"
	"Window/GLFWWindow.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC} ${EVENTSYSTEM} ${WINDOW})

source_group(" " FILES ${ROOT_SRC})
source_group("EventSystem" FILES ${EVENTSYSTEM})
source_group("Window" FILES ${WINDOW})


include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glm")

link_directories("${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017")
target_link_libraries(${PROJECT_NAME} "${SDK_DIR}/glfw-3.3.bin.WIN64/lib-vc2017/glfw3.lib")
include_directories(${PROJECT_NAME} PRIVATE "${SDK_DIR}/glfw-3.3.bin.WIN64/include")