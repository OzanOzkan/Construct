cmake_minimum_required(VERSION 3.10)

project (Input VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "Input.h"
  "Input.cpp"
)

include_directories("${SRC_DIR}/Common")

add_library (${PROJECT_NAME} SHARED ${ROOT_SRC})

source_group(" " FILES ${ROOT_SRC})

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
