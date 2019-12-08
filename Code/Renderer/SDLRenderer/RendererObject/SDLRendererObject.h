#pragma once

#include <Renderer/IRenderer.h>
#include <SDL.h>

class CSDLRendererObject
{
public:
	CSDLRendererObject(IRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);
	virtual ~CSDLRendererObject();

	SDL_Texture* getTexture() { return m_pSDLTexture; }
	void setTexture(SDL_Texture* pTexture) { m_pSDLTexture = pTexture; }

protected:
	IRenderer * m_pRendererContext = nullptr;
	SDL_Texture * m_pSDLTexture = nullptr;
	SDL_Renderer * m_pSDLRenderer = nullptr;
};