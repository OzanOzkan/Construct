#include "SDLRenderer.h"

#include <ILog.h>

#include "RendererObject/Sprite.h"
#include "RendererObject/Text.h"

/////////////////////////////////////////////////
CSDLRenderer::CSDLRenderer(ISystem * systemContext)
	: m_pSystem(systemContext)
{

}

/////////////////////////////////////////////////
void CSDLRenderer::InitializeModule()
{
	m_pSDLWindow = SDL_GetWindowFromID(GetSystem()->getWindowId());
	m_pSDLRenderer = SDL_CreateRenderer(m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(m_pSDLRenderer, 800, 600);

	if (TTF_Init() == -1)
		GetSystem()->GetLogger()->Log("Renderer [SDL2]: TTF initialization failed!");

	GetSystem()->GetLogger()->Log("Renderer Initialized: SDL2");
}

/////////////////////////////////////////////////
void CSDLRenderer::onUpdate()
{
	doRender();
}

/////////////////////////////////////////////////
IRendererObject * CSDLRenderer::CreateRenderObject(const SRenderObjectCreateParams & params)
{
	std::unique_ptr<IRendererObject> pRenderObject = nullptr;

	switch (params.type)
	{
	case ERendererObjectType::eRT_SPRITE:
	{
		pRenderObject = std::make_unique<CSprite>(this, m_pSDLRenderer);
	}
	break;
	case ERendererObjectType::eRT_TEXT:
	{
		pRenderObject = std::make_unique<CText>(this, m_pSDLRenderer);
	}
	break;
	}
		
	pRenderObject->Load(params);
	pRenderObject->setId(m_renderObjectList.size() > 0 ? m_renderObjectList.rbegin()->first + 1 : 0);

	return static_cast<IRendererObject*>(m_renderObjectList.insert(
		std::make_pair(pRenderObject->getId(),
			std::move(pRenderObject)
		)
	).first->second.get());
}

/////////////////////////////////////////////////
void CSDLRenderer::RemoveRenderObject(IRendererObject* pRenderObject)
{
	m_renderObjectList.erase(pRenderObject->getId());
}

/////////////////////////////////////////////////
int CSDLRenderer::LoadTexture(const std::string & filePath)
{
	int id = 0;
	if (m_loadedTextures.size() > 0)
	{
		id = m_loadedTextures.rbegin()->first + 1;
	}

	m_loadedTextures.emplace(std::make_pair(id, IMG_LoadTexture(m_pSDLRenderer, filePath.c_str())));

	return id;
}

/////////////////////////////////////////////////
void CSDLRenderer::UnloadTexture(const int & textureId)
{
	if (m_loadedTextures.size() > 1)
	{
		if (SDL_Texture* pTexture = m_loadedTextures.at(textureId))
		{
			m_loadedTextures.erase(textureId);

			SDL_DestroyTexture(pTexture);
		}
	}
}

/////////////////////////////////////////////////
void CSDLRenderer::doRender()
{
	SDL_RenderClear(m_pSDLRenderer);

	for (auto& pRenderObjectEntry : m_renderObjectList)
	{
		IRendererObject* pRendererObject = pRenderObjectEntry.second.get();

		if (!pRendererObject->isRenderActive())
			continue;

		SDL_Texture* texture = nullptr;

		SDL_Rect rect;
		rect.x = pRendererObject->getPosX();
		rect.y = pRendererObject->getPosY();
		rect.w = pRendererObject->getWidth();
		rect.h = pRendererObject->getHeight();

		switch (pRendererObject->getType())
		{
		case ERendererObjectType::eRT_SPRITE:
		{
			CSprite* pSprite = static_cast<CSprite*>(pRendererObject);
			texture = pSprite->getTexture();
		}
		break;
		case ERendererObjectType::eRT_TEXT:
		{
			CText* pText = static_cast<CText*>(pRendererObject);
			texture = pText->getTexture();
		}
		break;
		}

		SDL_RenderCopy(m_pSDLRenderer, texture, NULL, &rect);
	}

	SDL_RenderPresent(m_pSDLRenderer);
}

/*
/////////////////////////////////////////////////
void CSDLRenderer::doRender()
{
	SDL_RenderClear(m_pSDLRenderer);

	for(auto& pRenderObjectEntry : m_renderObjectList)
	{
		IRendererObject* pRenderObject = pRenderObjectEntry.second.get();

		if (!pRenderObject->isRenderActive())
			continue;

		// MOVE RENDEREROBJECTS TO SDL RENDERER. WRAPPER NEEDED.
		switch (pRenderObject->getType())
		{
		case ERendererObjectType::eRT_SPRITE:
		{
			ISprite* pSprite = static_cast<ISprite*>(pRenderObject);
			SDL_Rect texr;
			texr.x = pRenderObject->getPosX();
			texr.y = pRenderObject->getPosY();
			texr.w = pSprite->getWidth();
			texr.h = pSprite->getHeight();

			SDL_RenderCopy(m_pSDLRenderer, m_loadedTextures.at(static_cast<ISprite*>(pRenderObject)->getTextureId()), NULL, &texr);
		}
		break;
		case ERendererObjectType::eRT_TEXT:
		{
			IText* pText = static_cast<IText*>(pRenderObject);

			TTF_Font* Sans = TTF_OpenFont(pText->getFont().c_str(), pText->getFontSize()); 
			SDL_Color colWhite = { 255, 255, 255 }; 
			SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, pText->getText().c_str(), colWhite);
			SDL_Texture* Message = SDL_CreateTextureFromSurface(m_pSDLRenderer, surfaceMessage); //now you can convert it into a texture

			SDL_Rect Message_rect; //create a rect
			Message_rect.x = 0;  //controls the rect's x coordinate 
			Message_rect.y = 0; // controls the rect's y coordinte
			Message_rect.w = 100; // controls the width of the rect
			Message_rect.h = 100; // controls the height of the rect

								  //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

								  //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

			SDL_RenderCopy(m_pSDLRenderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

																	//Don't forget too free your surface and texture
		}
		break;
		}
	}

	SDL_RenderPresent(m_pSDLRenderer);

	//int w, h;
	//SDL_Texture* pImg = IMG_LoadTexture(m_pSDLRenderer, IMG);
	//SDL_QueryTexture(pImg, NULL, NULL, &w, &h);

	//SDL_Texture* pImg2 = IMG_LoadTexture(m_pSDLRenderer, IMG2);
	//SDL_QueryTexture(pImg2, NULL, NULL, &w, &h);

	//// clear the screen
	//SDL_RenderClear(m_pSDLRenderer);
	//// copy the texture to the rendering context

	//SDL_Rect texr; texr.x = 0; texr.y = 0; texr.w = 800; texr.h = 600;
	//SDL_RenderCopy(m_pSDLRenderer, pImg, NULL, &texr);

	//static float y = 0.f;
	//if (y < 500)
	//	y += 1.f;
	//else
	//	y = 0;

	//SDL_Rect texr2; texr2.x = 50; texr2.y = y; texr2.w = 70; texr2.h = 100;
	//SDL_RenderCopy(m_pSDLRenderer, pImg2, NULL, &texr2);

	// flip the backbuffer
	// this means that everything that we prepared behind the screens is actually shown
	//SDL_RenderPresent(m_pSDLRenderer);

	//SDL_DestroyTexture(pImg);
	//SDL_DestroyTexture(pImg2);
}
*/