#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"

#include <SDL_ttf.h>

class IRenderer;

class CSDLText : public IText, public CSDLRendererObject
{
public:
	CSDLText(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	void Load(const SRenderObjectParams& params) override;
	void RenderCopy() override;

	void PrepareText();

private:
	std::string m_previousText;
	TTF_Font* m_pSDLFont;
	SDL_Surface* m_pSDLSurface;
};