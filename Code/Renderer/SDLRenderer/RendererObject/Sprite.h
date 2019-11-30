#pragma once

#include <Renderer/IRenderObject.h>
#include <SDL.h>
#include <SDL_image.h>

class IRenderer;

class CSprite : public ISprite
{
public:
	CSprite(IRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	void Load(const SRenderObjectCreateParams& params) override;
	void setFile(const std::string& file) override;

	SDL_Texture* getTexture();

protected:
	void setTexture(SDL_Texture* pTexture) { m_pTexture = pTexture; }

private:
	IRenderer * m_pRendererContext = nullptr;
	SDL_Renderer* m_pSDLRenderer = nullptr;
	SDL_Texture* m_pTexture = nullptr;
};