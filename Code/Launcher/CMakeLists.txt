cmake_minimum_required(VERSION 3.10)

project (Launcher VERSION 1.0 LANGUAGES CXX)

file(GLOB ROOT_SRC
  "Main.cpp"
)

include_directories("${SRC_DIR}/Common")

add_executable(${PROJECT_NAME} ${ROOT_SRC})

source_group(" " FILES ${ROOT_SRC})

add_dependencies(${PROJECT_NAME} Renderer)
