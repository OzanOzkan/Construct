cmake_minimum_required(VERSION 3.10)
project (ProjectO01_Construct VERSION 1.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/Code")
set(SDK_DIR "${PROJECT_SOURCE_DIR}/SDKs")

# 3rd Party Libraries
## SDL2
set(SDL2_DIR "${SDK_DIR}/SDL2-2.0.12")
set(SDL2_TTF_INCLUDE_DIR "${SDK_DIR}/SDL2_ttf-2.0.15/include")
set(SDL2_IMAGE_INCLUDE_DIR "${SDK_DIR}/SDL2_image-2.0.5/include")
set(SDL2_IMAGE_LIBRARY "${SDK_DIR}/SDL2_image-2.0.5/lib/x64/SDL2_image.lib")
set(SDL2_TTF_LIBRARY "${SDK_DIR}/SDL2_ttf-2.0.15/lib/x64/SDL2_ttf.lib")

## Box2D
set(BOX2D_DIR "${SDK_DIR}/Box2D/")
set(BOX2D_INCLUDE_DIR "${BOX2D_DIR}/include")
set(BOX2D_LIBRARY "${BOX2D_DIR}/src/Debug/box2d.lib")
#add_subdirectory(${BOX2D_DIR})

## QT
set(Qt5_DIR "${SDK_DIR}/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5")
# ~3rd Party Libraries

add_subdirectory(Code)