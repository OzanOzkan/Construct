#include "SDLPolygon.h"

/////////////////////////////////////////////////
CSDLPolygon::CSDLPolygon(CSDLRenderer* pRendererContext, SDL_Renderer* pSDLRenderer)
	: CSDLRendererObject(pRendererContext, pSDLRenderer)
{
}

/////////////////////////////////////////////////
void CSDLPolygon::Load(const SRenderObjectParams& params)
{
	m_color = params.color;
}

/////////////////////////////////////////////////
void CSDLPolygon::RenderCopy()
{
	SDL_SetRenderDrawColor(m_pSDLRenderer, m_color.r, m_color.g, m_color.b, m_color.a);

	for (size_t i = 0; i < m_vertices.size(); ++i) {

		if (i + 1 < m_vertices.size()) {
			SDL_RenderDrawLine(m_pSDLRenderer,
				m_vertices[i].x, m_vertices[i].y,
				m_vertices[i + 1].x, m_vertices[i + 1].y);
		}
		//else {
		//	SDL_RenderDrawLine(m_pSDLRenderer,
		//		m_vertices[i].x, m_vertices[i].y,
		//		m_vertices[0].x, m_vertices[0].y);
		//}
	}
}
