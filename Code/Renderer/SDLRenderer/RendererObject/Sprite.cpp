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

	setType(ERendererObjectType::eRT_SPRITE);
	setFile(spriteParams.spriteFile.c_str());
	setTexture(IMG_LoadTexture(m_pSDLRenderer, spriteParams.spriteFile.c_str()));
	setSize(spriteParams.width, spriteParams.height);
	setPosition(spriteParams.posX, spriteParams.posY);

	setTexture(IMG_LoadTexture(m_pSDLRenderer, m_file.c_str()));
}

/////////////////////////////////////////////////
void CSprite::RenderCopy()
{
	SDL_Rect rect;
	rect.x = getPosX();
	rect.y = getPosY();
	rect.w = getWidth();
	rect.h = getHeight();

	SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &rect);
}

/////////////////////////////////////////////////
void CSprite::setFile(const std::string & file)
{
	m_file = file;
}
