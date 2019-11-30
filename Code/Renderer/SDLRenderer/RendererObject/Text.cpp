#include "Text.h"

CText::CText(IRenderer * rendererContext, SDL_Renderer* pSDLRenderer)
	: m_pRenderer(rendererContext)
	, m_pSDLRenderer(pSDLRenderer)
{
}

void CText::Load(const SRenderObjectCreateParams& params)
{
	const STextCreateParams& textParams = static_cast<const STextCreateParams&>(params);

	setType(ERendererObjectType::eRT_TEXT);
	setText(textParams.text);
	setFont(textParams.font);
	setFontSize(textParams.fontSize);
	setPosition(textParams.posX, textParams.posY);
	setSize(textParams.width, textParams.height);

	TTF_Font* font = TTF_OpenFont(getFont().c_str(), getFontSize());
	SDL_Color colWhite = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, getText().c_str(), colWhite);

	setTexture(SDL_CreateTextureFromSurface(m_pSDLRenderer, surfaceMessage));
}

SDL_Texture * CText::getTexture()
{
	return m_pTexture;
}
