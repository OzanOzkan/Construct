#include "Sprite.h"

#include <Renderer/IRenderer.h>

CSprite::CSprite(IRenderer* pRendererContext, SDL_Renderer* pSDLRenderer)
	: m_pRendererContext(pRendererContext)
	, m_pSDLRenderer(pSDLRenderer)
{
}

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

void CSprite::setFile(const std::string & file)
{
	m_file = file;
}

SDL_Texture* CSprite::getTexture()
{
	return m_pTexture;
}
