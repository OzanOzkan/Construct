#include "SDLAnimatedSprite.h"

#include "../SDLTextureManager.h"

#include <SDL_image.h>

/////////////////////////////////////////////////
CSDLAnimatedSprite::CSDLAnimatedSprite(CSDLRenderer * pRendererContext, SDL_Renderer * pSDLRenderer)
	: CSDLRendererObject(pRendererContext, pSDLRenderer)
	, m_animationFrames({})
	, m_lastRenderedFrame(0)
	, m_animationSpeed(0)
{
}

/////////////////////////////////////////////////
void CSDLAnimatedSprite::Load(const SRenderObjectParams & params)
{
	const SAnimatedSpriteParams& animatedSpriteParams = static_cast<const SAnimatedSpriteParams&>(params);
	CSDLTextureManager* pTextureManager = m_pRendererContext->GetTextureManager();

	m_type				= ERendererObjectType::eRT_SPRITE;
	m_position			= animatedSpriteParams.position;
	m_rotation			= animatedSpriteParams.rotation;
	m_class				= animatedSpriteParams.renderObjectClass;
	m_color				= animatedSpriteParams.color;
	m_animationSpeed	= animatedSpriteParams.animationSpeed;

	for (auto animationSequenceFile : animatedSpriteParams.getFrameFiles())
	{
		m_animationFrames.emplace_back(pTextureManager->GetTexture(pTextureManager->LoadTexture(animationSequenceFile)));
	}

	if (!m_animationFrames.empty())
	{
		int originalWidth, originalHeight;
		SDL_QueryTexture(m_animationFrames.front()->GetSDLTexturePtr(), NULL, NULL, &originalWidth, &originalHeight);

		m_width = animatedSpriteParams.width > -1 ? animatedSpriteParams.width : originalWidth;
		m_height = animatedSpriteParams.height > -1 ? animatedSpriteParams.height : originalHeight;
	}
}

/////////////////////////////////////////////////
void CSDLAnimatedSprite::RenderCopy()
{
	if (m_animationFrames.empty())
		return;

	static int frameCount = 0;

	if (frameCount == m_animationSpeed)
	{
		if (m_lastRenderedFrame < m_animationFrames.size() - 1)
			m_lastRenderedFrame++;
		else
			m_lastRenderedFrame = 0;
	}
	else if (frameCount > m_animationSpeed)
	{
		frameCount = 0;
	}

	SDL_Rect originalPosition;
	originalPosition.x = m_position.x;
	originalPosition.y = m_position.y;
	originalPosition.w = m_width;
	originalPosition.h = m_height;

	SDL_RenderCopyEx(m_pSDLRenderer,
		m_animationFrames[m_lastRenderedFrame]->GetSDLTexturePtr(), NULL, &originalPosition, m_rotation, NULL, SDL_FLIP_NONE);

	frameCount++;
}

/////////////////////////////////////////////////
int CSDLAnimatedSprite::getFrameCount()
{
	return m_animationFrames.size();
}

/////////////////////////////////////////////////
int CSDLAnimatedSprite::getCurrentFrame()
{
	return m_lastRenderedFrame;
}

/////////////////////////////////////////////////
void CSDLAnimatedSprite::setAnimationSpeed(const int & speed)
{
	m_animationSpeed = speed;
}
