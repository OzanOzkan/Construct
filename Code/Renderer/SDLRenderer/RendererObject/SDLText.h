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

protected:
	struct SSDLTextLine
	{
		SDL_Texture* texture;
		SDL_Rect rect;

		SSDLTextLine(SDL_Texture* t, SDL_Rect r)
			: texture(t)
			, rect(r)
		{};
	};

private:
	std::string m_previousText;
	std::vector<SSDLTextLine> m_textLines;
	TTF_Font* m_pSDLFont;
	SDL_Surface* m_pSDLSurface;
};