#include "SDLRendererObject.h"

/////////////////////////////////////////////////
CSDLRendererObject::CSDLRendererObject(IRenderer * pRendererContext, SDL_Renderer * pSDLRenderer)
	: m_pRendererContext(pRendererContext)
	, m_pSDLRenderer(pSDLRenderer)
	, m_pSDLTexture(nullptr)
{
}

/////////////////////////////////////////////////
CSDLRendererObject::~CSDLRendererObject()
{
	if(m_pSDLTexture)
		SDL_DestroyTexture(m_pSDLTexture);
}
