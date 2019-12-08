#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"
#include <SDL_image.h>

class IRenderer;

class CSprite : public ISprite, 
				public CSDLRendererObject
{
public:
	CSprite(IRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	// ISprite
	void Load(const SRenderObjectCreateParams& params) override;
	void setFile(const std::string& file) override;
	// ~ISprite

	void RenderCopy() override;
};