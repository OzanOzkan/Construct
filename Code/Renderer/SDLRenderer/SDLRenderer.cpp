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