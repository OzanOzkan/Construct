#include "SDLWindow.h"

#include <ILog.h>

/////////////////////////////////////////////////
CSDLWindow::CSDLWindow(ISystem* systemContext)
	: CWindow(systemContext)
	, m_pSDLWindow(nullptr)
	, m_pSDLSurface(nullptr)
{
}

/////////////////////////////////////////////////
void CSDLWindow::openWindow(const int & height, const int & width, TEventCallbackFn callbackFn, void* renderTarget)
{
	m_callbackFn = callbackFn;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		GetSystem()->GetLogger()->Log("SDL could not initialized!");
	}
	
#ifdef _WIN32
	if(renderTarget)
		m_pSDLWindow = SDL_CreateWindowFrom(renderTarget);
	else
		m_pSDLWindow = SDL_CreateWindow("Construct (SDL2)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
#else
	//Get device display mode
	SDL_Rect gScreenRect = { 0, 0, 320, 240 };
	SDL_DisplayMode displayMode;
	if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
	{
		gScreenRect.w = displayMode.w;
		gScreenRect.h = displayMode.h;
	}

	//Create window
	m_pSDLWindow = SDL_CreateWindow("Construct (SDL2)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
#endif

	if (!m_pSDLWindow)
	{
		GetSystem()->GetLogger()->Log("CSDLWindow::openWindow: Failed to create SDL window.");
		return;
	}

	//SDL_GL_CreateContext(m_pSDLWindow);
	m_pSDLSurface = SDL_GetWindowSurface(m_pSDLWindow);

	//// Use v-sync
	//SDL_GL_SetSwapInterval(1);

	// Get real window size and override if it is already set while window creation.
	SDL_GetWindowSize(m_pSDLWindow, &m_width, &m_height);
}

/////////////////////////////////////////////////
void CSDLWindow::closeWindow()
{
	//Destroy window
	SDL_DestroyWindow(m_pSDLWindow);

	//Quit SDL subsystems
	SDL_Quit();
}

/////////////////////////////////////////////////
void CSDLWindow::onUpdate()
{
	//Handle events on queue
	while (SDL_PollEvent(&m_SDLEvent) != 0)
	{
		handleEvent(m_SDLEvent);
	}
}

void CSDLWindow::setWindowSize(const int& width, const int& height)
{
	m_width = width;
	m_height = height;
	SDL_SetWindowSize(m_pSDLWindow, m_width, m_height);
}

/////////////////////////////////////////////////
void CSDLWindow::handleEvent(const SDL_Event & SDLEvent)
{
   	switch (SDLEvent.type)
	{
	case SDL_QUIT:
	{
		m_quit = true;
	}
	break;
	}
}
