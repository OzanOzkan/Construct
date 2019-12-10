#include "Sprite.h"

#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
CSprite::CSprite(IRenderer* pRendererContext, SDL_Renderer* pSDLRenderer)
	: CSDLRendererObject(pRendererContext, pSDLRenderer)
{
}

/////////////////////////////////////////////////
void CSprite::Load(const SRenderObjectCreateParams& params)
{
	const SSpriteCreateParams& spriteParams = static_cast<const SSpriteCreateParams&>(params);

	m_type			= ERendererObjectType::eRT_SPRITE;
	m_file			= spriteParams.spriteFile.c_str();
	m_width			= spriteParams.width;
	m_height		= spriteParams.height;
	m_position		= spriteParams.position;
	m_pSDLTexture	= IMG_LoadTexture(m_pSDLRenderer, m_file.c_str());
}

/////////////////////////////////////////////////
void CSprite::RenderCopy()
{
	SDL_Rect rect;
	rect.x = m_position.x;
	rect.y = m_position.y;
	rect.w = m_width;
	rect.h = m_height;

	SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &rect);
}

/////////////////////////////////////////////////
void CSprite::setFile(const std::string & file)
{
	m_file = file;
}
