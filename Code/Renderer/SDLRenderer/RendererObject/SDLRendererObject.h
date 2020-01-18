#pragma once

#include <System/ISystem.h>
#include <ILog.h>

#include <SDL.h>
#include "../SDLRenderer.h"

class CSDLRendererObject
{
public:
	CSDLRendererObject(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);
	virtual ~CSDLRendererObject();

	SDL_Texture* getTexture() { return m_pSDLTexture; }
	void setTexture(SDL_Texture* pTexture) { m_pSDLTexture = pTexture; }

protected:
	CSDLRenderer * m_pRendererContext;
	SDL_Texture * m_pSDLTexture;
	SDL_Renderer * m_pSDLRenderer;
};