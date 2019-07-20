cmake_minimum_required(VERSION 3.10)

project (System VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "Log.h"
  "Log.cpp"
  "System.h"
  "System.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC})

source_group(" " FILES ${ROOT_SRC})
