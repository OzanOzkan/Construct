#include "SDLRenderer.h"

#include <ILog.h>

#include "../RendererObject/Sprite.h"

/////////////////////////////////////////////////
CSDLRenderer::CSDLRenderer(SEnvironment * env)
	: m_pEnv(env)
{

}

/////////////////////////////////////////////////
void CSDLRenderer::InitializeModule()
{
	m_pSDLWindow = SDL_GetWindowFromID(m_pEnv->pSystem->getWindowId());
	m_pSDLRenderer = SDL_CreateRenderer(m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED);

	m_pEnv->pLog->Log("Renderer Initialized: SDL2");
}

/////////////////////////////////////////////////
void CSDLRenderer::onUpdate()
{
	doRender();
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
ISprite * CSDLRenderer::CreateSprite(const SSpriteCreateParams & params)
{
	std::unique_ptr<CSprite> pRenderObject = std::make_unique<CSprite>(this);
	pRenderObject->setId(m_renderObjectList.size() > 0 ? m_renderObjectList.rbegin()->first + 1 : 0);
	pRenderObject->setType(ERendererObjectType::eRT_SPRITE);
	pRenderObject->setFile(params.spriteFile.c_str());
	pRenderObject->setSize(params.w, params.h);
	pRenderObject->setPosition(params.posX, params.posY);
	pRenderObject->Load();

	return static_cast<ISprite*>(m_renderObjectList.insert(
			std::make_pair(pRenderObject->getId(),
				std::move(pRenderObject)
			)
	).first->second.get());
}

/////////////////////////////////////////////////
void CSDLRenderer::RemoveSprite(ISprite* pSprite)
{
	m_renderObjectList.erase(pSprite->getId());
}

/////////////////////////////////////////////////
//void CSDLRenderer::RenderSprite(const SSpriteRenderParams& params)
//{
//	if (SDL_Texture* pTexture = m_loadedTextures.at(params.texture_id))
//	{
//		m_sprites.emplace(params);
//	}
//}

/////////////////////////////////////////////////
void CSDLRenderer::doRender()
{
	SDL_RenderClear(m_pSDLRenderer);

	for(auto& pRenderObjectEntry : m_renderObjectList)
	{
		IRendererObject* pRenderObject = pRenderObjectEntry.second.get();

		if (!pRenderObject->isRenderActive())
			continue;

		switch (pRenderObject->getType())
		{
		case ERendererObjectType::eRT_SPRITE:
		{
			SDL_Rect texr;
			texr.x = pRenderObject->getPosX();
			texr.y = pRenderObject->getPosY();
			texr.w = static_cast<ISprite*>(pRenderObject)->getWidth(); 
			texr.h = static_cast<ISprite*>(pRenderObject)->getHeight();

			SDL_RenderCopy(m_pSDLRenderer, m_loadedTextures.at(static_cast<ISprite*>(pRenderObject)->getTextureId()), NULL, &texr);
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