#include "SDLRect.h"

/////////////////////////////////////////////////
CSDLRect::CSDLRect(CSDLRenderer * pRendererContext, SDL_Renderer * pSDLRenderer)
	: CSDLRendererObject(pRendererContext, pSDLRenderer)
{
}

/////////////////////////////////////////////////
void CSDLRect::Load(const SRenderObjectParams & params)
{
	m_position	= params.position;
	m_rotation	= params.rotation;
	m_width		= params.width;
	m_height	= params.height;
	m_color		= params.color;
}

/////////////////////////////////////////////////
void CSDLRect::RenderCopy()
{
	// TODO: Rotation.
	SDL_Rect drawRect;
	drawRect.x = m_position.x;
	drawRect.y = m_position.y;
	drawRect.w = m_width;
	drawRect.h = m_height;

	SDL_SetRenderDrawColor(m_pSDLRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawRect(m_pSDLRenderer, &drawRect);
}
