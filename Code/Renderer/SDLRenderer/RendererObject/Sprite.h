#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"
#include <SDL_image.h>

class IRenderer;

class CSprite : public ISprite, 
				public CSDLRendererObject
{
public:
	CSprite(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	// ISprite
	void Load(const SRenderObjectParams& params) override;
	void setFile(const std::string& file) override;
	// ~ISprite

	void RenderCopy() override;

private:
	bool m_scrollingSprite;
	float m_scrollOffset;
	float m_scrollSpeed;
	SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection m_scrollDirection;
};