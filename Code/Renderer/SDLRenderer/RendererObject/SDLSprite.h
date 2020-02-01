#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"

class CSDLSprite : public ISprite, public CSDLRendererObject
{
public:
	CSDLSprite(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	// ISprite
	void Load(const SRenderObjectParams& params) override;
	void setFile(const std::string& file) override;
	// ~ISprite

	void RenderCopy() override;

private:
	bool m_scrollingSprite = false;
	float m_scrollOffset = -1;
	float m_scrollSpeed = -1;
	SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection m_scrollDirection;
};