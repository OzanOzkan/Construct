#include "SDLRenderer.h"

#include <ILog.h>

#include "RendererObject/SDLRendererObject.h"
#include "RendererObject/Sprite.h"
#include "RendererObject/Text.h"

/////////////////////////////////////////////////
CSDLRenderer::CSDLRenderer(ISystem * systemContext)
	: m_pSystem(systemContext)
	, m_pTextureManager(nullptr)
	, m_pSDLWindow(nullptr)
	, m_pSDLRenderer(nullptr)
	, m_renderObjectList()
{
}

/////////////////////////////////////////////////
void CSDLRenderer::InitializeModule()
{
	m_pSDLWindow = SDL_GetWindowFromID(GetSystem()->GetWindowManager()->GetWindowId());
	if(!m_pSDLWindow) GetSystem()->GetLogger()->Log("CSDLRenderer::InitializeModule(): Window Failure!");

	SDL_DestroyRenderer(SDL_GetRenderer(m_pSDLWindow));
	m_pSDLRenderer = SDL_CreateRenderer(m_pSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!m_pSDLRenderer) {
		GetSystem()->GetLogger()->Log("CSDLRenderer::InitializeModule(): SDL Renderer creation failed!");
        //SDL_Log("ERROR: %s", SDL_GetError());
    }

	//SDL_RenderSetLogicalSize(m_pSDLRenderer, 1920, 1080);

	if (TTF_Init() == -1)
		GetSystem()->GetLogger()->Log("Renderer [SDL2]: TTF initialization failed!");

	//LoadTextures();

	GetSystem()->GetLogger()->Log("Renderer Initialized: SDL2");

	// Initialize Texture Manager
	m_pTextureManager = std::make_unique<CSDLTextureManager>(m_pSystem, m_pSDLRenderer);
}

/////////////////////////////////////////////////
void CSDLRenderer::onUpdate()
{
	doRender();
}

/////////////////////////////////////////////////
IRendererObject * CSDLRenderer::CreateRenderObject(const SRenderObjectParams & params)
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
		
	pRenderObject->setId(m_renderObjectList.size() > 0 ? m_renderObjectList.rbegin()->first + 1 : 0);
	pRenderObject->Load(params);
	
	m_renderLayerMap.emplace(params.layerId, pRenderObject->getId());
	
	return static_cast<IRendererObject*>(m_renderObjectList.insert(
		std::make_pair(pRenderObject->getId(),
			std::move(pRenderObject)
		)
	).first->second.get());
}

/////////////////////////////////////////////////
void CSDLRenderer::RemoveRenderObject(IRendererObject* pRenderObject)
{
	// Remove object from the layer map.
	for (auto layerItr = m_renderLayerMap.begin(); layerItr != m_renderLayerMap.end(); ++layerItr)
	{
		if (layerItr->second == pRenderObject->getId())
		{
			m_renderLayerMap.erase(layerItr);
			break;
		}
	}

	// And remove object from the list.
	m_renderObjectList.erase(pRenderObject->getId());
}

/////////////////////////////////////////////////
void CSDLRenderer::doRender()
{
	// Clear SDL renderer.
	SDL_RenderClear(m_pSDLRenderer);

	for (auto& pRenderLayerEntry : m_renderLayerMap)
	{
		auto pRenderObject = m_renderObjectList.find(pRenderLayerEntry.second);
		IRendererObject* pRendererObject = pRenderObject->second.get();

		// Do not render if object render is not active.
		if (!pRendererObject->isRenderActive())
			continue;

		// Load object position, size and texture to SDL Renderer.
		pRendererObject->RenderCopy();
	}

	// Present prepared SDL renderer.
	SDL_RenderPresent(m_pSDLRenderer);
}