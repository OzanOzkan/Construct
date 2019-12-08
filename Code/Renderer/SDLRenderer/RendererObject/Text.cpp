#include "Text.h"

/////////////////////////////////////////////////
CText::CText(IRenderer * pRendererContext, SDL_Renderer* pSDLRenderer)
	: CSDLRendererObject(pRendererContext, pSDLRenderer)
	, m_previousText("")
{
}

/////////////////////////////////////////////////
void CText::Load(const SRenderObjectCreateParams& params)
{
	const STextCreateParams& textParams = static_cast<const STextCreateParams&>(params);

	setType(ERendererObjectType::eRT_TEXT);
	setText(textParams.text);
	setFont(textParams.font);
	setFontSize(textParams.fontSize);
	setPosition(textParams.posX, textParams.posY);
	setSize(textParams.width, textParams.height);

	PrepareText();
}

/////////////////////////////////////////////////
void CText::RenderCopy()
{
	PrepareText();

	SDL_Rect rect;
	rect.x = getPosX();
	rect.y = getPosY();
	rect.w = getWidth();
	rect.h = getHeight();

	SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &rect);
}

/////////////////////////////////////////////////
void CText::PrepareText()
{
	if (m_text != m_previousText)
	{
		TTF_Font* font = TTF_OpenFont(getFont().c_str(), getFontSize());
		SDL_Color colWhite = { 255, 255, 255 };
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, getText().c_str(), colWhite);

		int w, h;
		TTF_SizeText(font, getText().c_str(), &w, &h);
		m_width = static_cast<float>(w);
		m_height = static_cast<float>(h);

		if (m_pSDLTexture)
			SDL_DestroyTexture(m_pSDLTexture);

		setTexture(SDL_CreateTextureFromSurface(m_pSDLRenderer, surfaceMessage));

		m_previousText = m_text;
	}
}