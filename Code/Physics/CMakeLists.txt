cmake_minimum_required(VERSION 3.10)

project (Physics VERSION 1.0 LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(ROOT_SRC
  "Physics.cpp"
)

set(BOX2DPHYSICS_SRC
	"B2DPhysics/B2DPhysics.h"
	"B2DPhysics/B2DPhysics.cpp"
)

set(BOX2DOBJECT_SRC
	"B2DPhysics/B2DObject/B2DObject.h"
	"B2DPhysics/B2DObject/B2DObject.cpp"
	"B2DPhysics/B2DObject/B2DPhysicalObject.h"
	"B2DPhysics/B2DObject/B2DPhysicalObject.cpp"
	"B2DPhysics/B2DObject/B2DSensorObject.h"
	"B2DPhysics/B2DObject/B2DSensorObject.cpp"
)

source_group(" " FILES ${ROOT_SRC})
source_group("B2DPhysics" FILES ${BOX2DPHYSICS_SRC})
source_group("B2DPhysics" FILES ${BOX2DPHYSICS_SRC})
source_group("B2DPhysics\\B2DObject" FILES ${BOX2DOBJECT_SRC})

#find_package(Box2D REQUIRED)

include_directories(${BOX2D_INCLUDE_DIR})

add_library (${PROJECT_NAME} 
	SHARED 
		${ROOT_SRC} 
		${BOX2DPHYSICS_SRC}
		${BOX2DOBJECT_SRC}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		Common
		${BOX2D_LIBRARY}
)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)