#pragma once

#include <Renderer/IRenderObject.h>
#include "SDLRendererObject.h"

class CSDLAnimatedSprite : public IAnimatedSprite, public CSDLRendererObject
{
public:
	CSDLAnimatedSprite(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer);

	void Load(const SRenderObjectParams & params) override;
	void RenderCopy() override;
	int getFrameCount() override;
	int getCurrentFrame() override;
	void setAnimationSpeed(const int & speed) override;

private:
	std::vector<CSDLTexture*> m_animationFrames;
	int m_lastRenderedFrame;
	float m_animationSpeed;
};