#include "Sprite.h"

#include <Renderer/IRenderer.h>

CSprite::CSprite(IRenderer* pRendererContext)
	: m_pRendererContext(pRendererContext)
{
}

void CSprite::Load()
{
	m_textureId = m_pRendererContext->LoadTexture(m_file);
}

void CSprite::setFile(const std::string & file)
{
	m_file = file;
}

void CSprite::setSize(const float & w, const float & h)
{
	m_width = w;
	m_height = h;
}

const int & CSprite::getTextureId() const
{
	return m_textureId;
}
