#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"

class CSDLPolygon : public IPolygon, public CSDLRendererObject
{
public:
	CSDLPolygon(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	void Load(const SRenderObjectParams& params) override;
	void RenderCopy() override;
};