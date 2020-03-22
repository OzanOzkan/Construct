cmake_minimum_required(VERSION 3.10)

project (WindowsLauncher VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
  "Main.cpp"
)

add_executable(${PROJECT_NAME} ${ROOT_SRC})

source_group(" " FILES ${ROOT_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC Common)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)