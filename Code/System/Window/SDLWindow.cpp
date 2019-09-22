#include "SDLWindow.h"

#include <ILog.h>

/////////////////////////////////////////////////
CSDLWindow::CSDLWindow(SEnvironment * env)
	: m_pEnv(env)
{
}

/////////////////////////////////////////////////
CSDLWindow::~CSDLWindow()
{
}

/////////////////////////////////////////////////
void CSDLWindow::openWindow(const int & height, const int & width, TEventCallbackFn callbackFn)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_LoadLibrary(NULL);

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_pSDLWindow = SDL_CreateWindow("Construct (SDL2)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!m_pSDLWindow)
	{
		m_pEnv->pLog->Log("CSDLWindow::openWindow: Failed to create SDL window.");
		return;
	}

	SDL_GL_CreateContext(m_pSDLWindow);
	m_pSDLSurface = SDL_GetWindowSurface(m_pSDLWindow);

	// Use v-sync
	SDL_GL_SetSwapInterval(1);
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
		m_pEnv->pLog->Log("SDL Event");
		//User requests quit
		if (m_SDLEvent.type == SDL_QUIT)
		{
			m_quit = true;
		}
	}

	SDL_GL_SwapWindow(m_pSDLWindow);
}