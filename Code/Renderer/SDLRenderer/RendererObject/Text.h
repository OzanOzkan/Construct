#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"

#include <SDL_ttf.h>

class IRenderer;

class CText : public IText
			, public CSDLRendererObject
{
public:
	CText(IRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	void Load(const SRenderObjectCreateParams& params) override;
	void RenderCopy() override;

	void PrepareText();

private:
	std::string m_previousText;
};