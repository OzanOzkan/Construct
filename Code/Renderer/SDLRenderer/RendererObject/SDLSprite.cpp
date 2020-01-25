#include "SDLSprite.h"

#include "../SDLTextureManager.h"

#include <SDL_image.h>

/////////////////////////////////////////////////
CSDLSprite::CSDLSprite(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer)
	: CSDLRendererObject(pRendererContext, pSDLRenderer)
	, m_scrollingSprite(false)
	, m_scrollOffset(0.f)
	, m_scrollSpeed(0.f)
	, m_scrollDirection(SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection::eSPD_NONE)
{
}

/////////////////////////////////////////////////
void CSDLSprite::Load(const SRenderObjectParams& params)
{
	const SSpriteParams& spriteParams = static_cast<const SSpriteParams&>(params);
	CSDLTextureManager* pTextureManager = m_pRendererContext->GetTextureManager();

	m_type				= ERendererObjectType::eRT_SPRITE;
	m_file				= spriteParams.spriteFile;
	m_position			= spriteParams.position;
	m_scrollingSprite	= (spriteParams.scrollParams.scrollSpeed > -1);
	m_scrollSpeed		= spriteParams.scrollParams.scrollSpeed;
	m_scrollDirection	= spriteParams.scrollParams.scrollDirection;
	m_pSDLTexture		= pTextureManager->GetTexture(pTextureManager->LoadTexture(spriteParams.spriteFile))->GetSDLTexturePtr();

	if (m_pSDLTexture)
	{
		int originalWidth, originalHeight;
		SDL_QueryTexture(m_pSDLTexture, NULL, NULL, &originalWidth, &originalHeight);

		m_width = spriteParams.width > -1 ? spriteParams.width : originalWidth;
		m_height = spriteParams.height > -1 ? spriteParams.height : originalHeight;
	}
}

/////////////////////////////////////////////////
void CSDLSprite::setFile(const std::string & file)
{
	m_file = file;
}

/////////////////////////////////////////////////
void CSDLSprite::RenderCopy()
{
	if (!m_pSDLTexture)
		return;

	SDL_Rect originalPosition;
	originalPosition.x = m_position.x;
	originalPosition.y = m_position.y;
	originalPosition.w = m_width;
	originalPosition.h = m_height;

	if (!m_scrollingSprite)
	{
		SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &originalPosition);
	}
	else
	{
		m_scrollOffset += m_scrollSpeed;
		if (m_scrollOffset >= m_height)
			m_scrollOffset = 0.f;

		SDL_Rect tile1;
		tile1.w = m_width;
		tile1.h = m_height;

		SDL_Rect tile2;
		tile2.w = m_width;
		tile2.h = m_height;

		switch (m_scrollDirection)
		{
		case SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection::eSPD_UP:
		{
			tile1.x = m_position.x;
			tile1.y = m_position.y - m_scrollOffset;

			tile2.x = m_position.x;
			tile2.y = m_position.y + m_height - m_scrollOffset;
		}
		break;
		case SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection::eSPD_DOWN:
		{
			tile1.x = m_position.x;
			tile1.y = m_position.y + m_scrollOffset;

			tile2.x = m_position.x;
			tile2.y = m_position.y - m_height + m_scrollOffset;
		}
		break;
		case SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection::eSPR_RIGHT:
		{
			tile1.x = m_position.x - m_scrollOffset;
			tile1.y = m_position.y;

			tile2.x = m_position.x + m_height + m_scrollOffset;
			tile2.y = m_position.y;
		}
		break;
		case SSpriteParams::SSpriteScrollParams::ESpriteScrollDirection::eSPD_LEFT:
		{
			tile1.x = m_position.x + m_scrollOffset;
			tile1.y = m_position.y;

			tile2.x = m_position.x - m_height + m_scrollOffset;
			tile2.y = m_position.y;
		}
		break;
		}

		SDL_RenderSetClipRect(m_pSDLRenderer, &originalPosition);
		SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &tile1);
		SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &tile2);
		SDL_RenderSetClipRect(m_pSDLRenderer, NULL);
	}

	if (m_debugDraw)
		DebugDraw();
}

/////////////////////////////////////////////////
void CSDLSprite::DebugDraw()
{
	int layerId = 98;

	// Bounding box
	if (!m_pDebugRect)
	{
		SRectParams params;
		params.layerId = layerId;
		params.position = m_position;
		params.height = m_height;
		params.width = m_width;

		m_pDebugRect = (IRect*)m_pRendererContext->CreateRenderObject(params);
		m_pDebugRect->setRenderActive(true);
	}
	else
	{
		m_pDebugRect->setPosition(m_position);
	}

	// Text
	if (!m_pDebugText)
	{
		STextParams params;
		params.layerId = layerId;
		params.position = m_position - Vector2(0, 15);
		params.text = m_file;
		params.fontSize = 10;

		m_pDebugText = (IText*)m_pRendererContext->CreateRenderObject(params);
		m_pDebugText->setRenderActive(true);
	}
	else
	{
		m_pDebugText->setPosition(m_position - Vector2(0, 15));
	}
}
