#pragma once

#include <Renderer/IRenderObject.h>
#include <SDL.h>
#include <SDL_ttf.h>

class IRenderer;

class CText : public IText
{
public:
	CText(IRenderer* rendererContext, SDL_Renderer* pSDLRenderer);

	void Load(const SRenderObjectCreateParams& params) override;

	SDL_Texture* getTexture();

protected:
	void setTexture(SDL_Texture* pTexture) { m_pTexture = pTexture; }

private:
	IRenderer * m_pRenderer = nullptr;
	SDL_Renderer* m_pSDLRenderer = nullptr;
	SDL_Texture* m_pTexture = nullptr;
};