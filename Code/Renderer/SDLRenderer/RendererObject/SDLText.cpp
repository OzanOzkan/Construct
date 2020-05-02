#include "SDLText.h"

#include <sstream>

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
	m_rotation	= textParams.rotation;
	m_width		= textParams.width;
	m_height	= textParams.height;
	m_color		= textParams.color;

	if (m_font.empty())
	{
		m_font = m_pRendererContext->GetSystem()->getFileManager()->getAssetsDirectory() + "Fonts/ARIAL.TTF";
	}

	m_pSDLFont = TTF_OpenFont(getFont().c_str(), m_fontSize);

	PrepareText();
}

/////////////////////////////////////////////////
void CSDLText::RenderCopy()
{
	if (m_textLines.empty())
		return;

	if (m_text.compare(m_previousText) != 0) // Todo: Implement operator==
	{
		PrepareText();
		m_previousText = m_text;
	}

	for (auto textLine : m_textLines)
	{
		SDL_RenderCopyEx(m_pSDLRenderer, textLine.texture, NULL, &textLine.rect, m_rotation, NULL, SDL_FLIP_NONE);
	}
}

/////////////////////////////////////////////////
void CSDLText::PrepareText()
{
	const SDL_Color color = { m_color.r, m_color.g, m_color.b };

	for (auto textLine : m_textLines) {
		SDL_DestroyTexture(textLine.texture);
	}
	m_textLines.clear();

	int line = 0;
	std::stringstream text;
	text << m_text;
	for (std::string lineText; std::getline(text, lineText);)
	{
		SDL_Rect rect;
		TTF_SizeText(m_pSDLFont, lineText.c_str(), &rect.w, &rect.h);
		rect.x = m_position.x;
		rect.y = m_position.y + (line * m_fontSize);

		m_pSDLSurface = TTF_RenderText_Solid(m_pSDLFont, lineText.c_str(), color);

		m_textLines.emplace_back(SDL_CreateTextureFromSurface(m_pSDLRenderer, m_pSDLSurface), rect);

		SDL_FreeSurface(m_pSDLSurface);

		++line;
	}
}