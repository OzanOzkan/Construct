#include "SDLCamera.h"

/////////////////////////////////////////////////
CSDLCamera::CSDLCamera(ISystem * systemContext)
	: m_pSystem(systemContext)
	, m_position({})
	, m_zoomLevel(1.f)
	, m_width(0)
	, m_height(0)
{
}

/////////////////////////////////////////////////
void CSDLCamera::SetPosition(const Vector2 & position)
{
	m_position = position;
}

/////////////////////////////////////////////////
const Vector2 & CSDLCamera::GetPosition()
{
	return m_position;
}

/////////////////////////////////////////////////
void CSDLCamera::SetZoomLevel(const float& zoomLevel)
{
	m_zoomLevel = zoomLevel < 0.1f ? 0.1f : zoomLevel;
}

/////////////////////////////////////////////////
float CSDLCamera::GetZoomLevel()
{
	return m_zoomLevel;
}

/////////////////////////////////////////////////
void CSDLCamera::SetSize(const float & width, const float & height)
{
	m_width = width;
	m_height = height;
}

/////////////////////////////////////////////////
void CSDLCamera::GetSize(float & width, float & height)
{
	width = m_width;
	height = m_height;
}
