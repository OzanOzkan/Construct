#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"

class CSDLRect : public IRect, public CSDLRendererObject
{
public:
	CSDLRect(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	void Load(const SRenderObjectParams& params) override;
	void RenderCopy() override;
};