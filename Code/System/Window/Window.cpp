#include "Window.h"

/////////////////////////////////////////////////
CWindow::CWindow(ISystem* systemContext)
	: m_pSystem(systemContext)
	, m_quit(false)
	, m_height(-1)
	, m_width(-1)
{

}

/////////////////////////////////////////////////
const SWindowSize & CWindow::getWindowSize()
{
	SWindowSize size;
	size.height = m_height;
	size.width = m_width;

	return size;
}
