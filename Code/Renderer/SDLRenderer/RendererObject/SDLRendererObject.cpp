#include "SDLRendererObject.h"

/////////////////////////////////////////////////
CSDLRendererObject::CSDLRendererObject(IRenderer * pRendererContext, SDL_Renderer * pSDLRenderer)
	: m_pRendererContext(pRendererContext)
	, m_pSDLRenderer(pSDLRenderer)
{
}

/////////////////////////////////////////////////
CSDLRendererObject::~CSDLRendererObject()
{
}
