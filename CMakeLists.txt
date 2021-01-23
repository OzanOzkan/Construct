cmake_minimum_required(VERSION 3.11)
project (ProjectO01_Construct VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(PROJECT_SRC_DIR "${PROJECT_SOURCE_DIR}/Code" CACHE FILEPATH "")
set(PROJECT_SDK_DIR "F:/Development/ProjectO01.bak/SDKs" CACHE FILEPATH "")
#set(SDK_DIR "${PROJECT_SOURCE_DIR}/SDKs")
#set(EXTERNAL_DIR "${PROJECT_SOURCE_DIR}/External")
set(SOLUTION_DEPENDENCY_DIR "3rdParty")
list(APPEND CMAKE_PREFIX_PATH ${FETCHCONTENT_BASE_DIR} ${EXTERNAL_DIR})

set(PROJECT_INCLUDE_EDITOR OFF CACHE BOOL "Include editor to build")

################################################################################
### Fetching external content
################################################################################
cmake_policy(SET CMP0077 NEW) # Make the following calls actually override what is defined in option()

# SDL2
set(SDL2_VER "2.0.12")
set(SDL2_PROJECT_NAME "sdl2-${SDL2_VER}")
FetchContent_Declare(
    ${SDL2_PROJECT_NAME}
    GIT_REPOSITORY "https://github.com/SDL-mirror/SDL.git"
    GIT_TAG "release-${SDL2_VER}"
)

# SDL Image
set(SDL2_IMAGE_VER "2.0.5")
set(SDL2_IMAGE_PROJECT_NAME "sdl2_image-${SDL2_IMAGE_VER}")
FetchContent_Declare(
    ${SDL2_IMAGE_PROJECT_NAME}
    URL https://github.com/pvallet/SDL_image/archive/release-2.0.5-mod6.zip
)

# SDL TTF
set(SDL2_TTF_VER "2.0.15-mod1")
set(SDL2_TTF_PROJECT_NAME "sdl2_ttf-${SDL2_TTF_VER}")
FetchContent_Declare(${SDL2_TTF_PROJECT_NAME}
    GIT_REPOSITORY "https://github.com/OzanOzkan/SDL_ttf.git"
    GIT_TAG "release-${SDL2_TTF_VER}"
)

# Freetype (SDL TTF dependency)
set(FREETYPE_VER "2.9.1")
set(FREETYPE_PROJECT_NAME "freetype-${FREETYPE_VER}")
FetchContent_Declare(${FREETYPE_PROJECT_NAME}
	URL https://download.savannah.gnu.org/releases/freetype/freetype-2.9.1.tar.gz
)
FetchContent_MakeAvailable(${FREETYPE_PROJECT_NAME})
set(FREETYPE_INCLUDE_DIRS "${freetype-2.9.1_SOURCE_DIR}/include")
if(WIN32)
  set(FREETYPE_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Debug/freetyped.lib) # TODO
else()
  set(FREETYPE_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libfreetype.a)
endif()

# Do not build the static version of SDL
set(BUILD_SHARED_LIBS ON)

# To make libpng build correctly
set(ZLIB_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/${SDL2_IMAGE_PROJECT_NAME}-src/external/zlib-1.2.11)
set(ZLIB_LIBRARY zlib)

set(PNG_STATIC OFF CACHE BOOL "Build static lib")
set(PNG_TESTS  OFF CACHE BOOL "Build libpng tests")
set(SKIP_INSTALL_ALL ON) # Prevent png from trying to install stuff and fail
set(SUPPORT_JPG OFF CACHE BOOL "The jpeg build is not correctly set up and we don't need it right now")

set(SDL2_LIBRARY SDL2)
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_DIR ${CMAKE_BINARY_DIR}/_deps/${SDL2_PROJECT_NAME}-src)
set(SDL2_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/${SDL2_PROJECT_NAME}-src/include)

set(SDL2_IMAGE_LIBRARY SDL2_image)
set(SDL2_IMAGE_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/${SDL2_IMAGE_PROJECT_NAME}-src)

set(SDL2_TTF_LIBRARY SDL2_ttf)
set(SDL2_TTF_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/${SDL2_TTF_PROJECT_NAME}-src)

# Fixing the build of SDL on VS2019
if (MSVC)
  list(APPEND EXTRA_LIBS vcruntime)
endif()

FetchContent_MakeAvailable(${SDL2_PROJECT_NAME} ${SDL2_IMAGE_PROJECT_NAME} ${SDL2_TTF_PROJECT_NAME})

# Box2D
set(BOX2D_VER "2.4.0")
set(BOX2D_PROJECT_NAME "box2d-${BOX2D_VER}")
FetchContent_Declare(${BOX2D_PROJECT_NAME}
    GIT_REPOSITORY "https://github.com/erincatto/box2d.git"
    GIT_TAG 1025f9a10949b963d6311995910bdd04f72dae6c
)

set(BOX2D_INCLUDE_DIR "${box2d-2.4.0_SOURCE_DIR}/include")
set(BOX2D_LIBRARY box2d)
FetchContent_MakeAvailable(${BOX2D_PROJECT_NAME})
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "Build the Box2D unit tests" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "Build the Box2D unit tests" FORCE)

if(INCLUDE_EDITOR)
  ## QT
  set(Qt5_DIR "${PROJECT_SDK_DIR}/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5")
endif()
# ~3rd Party Libraries

# Filter dependencies in the solution explorer
set_target_properties(png freetype genfiles uninstall ${ZLIB_LIBRARY} PROPERTIES FOLDER ${SOLUTION_DEPENDENCY_DIR})
set_target_properties(${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} PROPERTIES FOLDER ${SOLUTION_DEPENDENCY_DIR})
set_target_properties(${BOX2D_LIBRARY} PROPERTIES FOLDER ${SOLUTION_DEPENDENCY_DIR})

add_subdirectory(${PROJECT_SRC_DIR})
