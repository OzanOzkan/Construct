cmake_minimum_required(VERSION 3.10)

project (Renderer VERSION 1.0 LANGUAGES CXX)

set(ROOT_SRC
  "Renderer.cpp"
)

set(SDL_RENDERER
	"SDLRenderer/SDLCamera.h"
	"SDLRenderer/SDLCamera.cpp"
	"SDLRenderer/SDLRenderer.h"
	"SDLRenderer/SDLRenderer.cpp"
	"SDLRenderer/SDLTexture.h"
	"SDLRenderer/SDLTexture.cpp"
	"SDLRenderer/SDLTextureManager.h"
	"SDLRenderer/SDLTextureManager.cpp"
)

set(RENDEREROBJECT
	"SDLRenderer/RendererObject/SDLRendererObject.h"
	"SDLRenderer/RendererObject/SDLRendererObject.cpp"
	"SDLRenderer/RendererObject/SDLSprite.h"
	"SDLRenderer/RendererObject/SDLSprite.cpp"
	"SDLRenderer/RendererObject/SDLAnimatedSprite.h"
	"SDLRenderer/RendererObject/SDLAnimatedSprite.cpp"
	"SDLRenderer/RendererObject/SDLText.h"
	"SDLRenderer/RendererObject/SDLText.cpp"
	"SDLRenderer/RendererObject/SDLRect.h"
	"SDLRenderer/RendererObject/SDLRect.cpp"
	"SDLRenderer/RendererObject/SDLPolygon.h"
	"SDLRenderer/RendererObject/SDLPolygon.cpp"
)

source_group(" " FILES ${ROOT_SRC})
source_group("SDLRenderer" FILES ${SDL_RENDERER})
source_group("SDLRenderer\\RendererObject" FILES ${RENDEREROBJECT})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
	${SDL2_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIRS}
)

add_library (${PROJECT_NAME}
	SHARED
		${ROOT_SRC}
		${SDL_RENDERER}
		${RENDEREROBJECT}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		Common
		${SDL2_LIBRARIES}
		${SDL2_IMAGE_LIBRARIES}
		${SDL2_TTF_LIBRARIES}
)

set_property (TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
