#include "SDLText.h"

/////////////////////////////////////////////////
CSDLText::CSDLText(CSDLRenderer * pRendererContext, SDL_Renderer* pSDLRenderer)
	: CSDLRendererObject(pRendererContext, pSDLRenderer)
	, m_previousText("")
	, m_pSDLFont(nullptr)
	, m_pSDLSurface(nullptr)
{
}

/////////////////////////////////////////////////
void CSDLText::Load(const SRenderObjectParams& params)
{
	const STextParams& textParams = static_cast<const STextParams&>(params);

	m_type		= ERendererObjectType::eRT_TEXT;
	m_text		= textParams.text;
	m_font		= textParams.font;
	m_fontSize	= textParams.fontSize;
	m_position	= textParams.position;
	m_width		= textParams.width;
	m_height	= textParams.height;

	if (m_font.empty())
	{
#ifdef _WIN32
		m_font = std::string(m_pRendererContext->GetSystem()->getFileManager()->getAssetsDirectory() + "Fonts\\ARIAL.TTF");
#else
		m_font = "Fonts/ARIAL.TTF";
#endif
	}

	m_pSDLFont = TTF_OpenFont(getFont().c_str(), m_fontSize);

	PrepareText();
}

/////////////////////////////////////////////////
void CSDLText::RenderCopy()
{
	if (!m_pSDLTexture)
		return;

	if (m_text.compare(m_previousText) != 0) // Todo: Implement operator==
	{
		PrepareText();
		m_previousText = m_text;
	}

	SDL_Rect rect;
	rect.x = m_position.x;
	rect.y = m_position.y;
	rect.w = m_width;
	rect.h = m_height;

	SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &rect);
}

/////////////////////////////////////////////////
void CSDLText::PrepareText()
{
	SDL_Color colWhite = { 255, 255, 255 };

	m_pSDLSurface = TTF_RenderText_Solid(m_pSDLFont, getText().c_str(), colWhite);

	int w, h;
	TTF_SizeText(m_pSDLFont, getText().c_str(), &w, &h);
	m_width = static_cast<float>(w);
	m_height = static_cast<float>(h);

	if(m_pSDLTexture) SDL_DestroyTexture(m_pSDLTexture);
	m_pSDLTexture = SDL_CreateTextureFromSurface(m_pSDLRenderer, m_pSDLSurface);

	SDL_FreeSurface(m_pSDLSurface);
}