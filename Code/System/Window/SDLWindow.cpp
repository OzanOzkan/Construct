/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "SDLWindow.h"

#include <ILog.h>

/////////////////////////////////////////////////
CSDLWindow::CSDLWindow(ISystem * systemContext)
	: CWindow(systemContext)
{
}

/////////////////////////////////////////////////
void CSDLWindow::openWindow(const int & height, const int & width, TEventCallbackFn callbackFn)
{
	m_callbackFn = callbackFn;

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	
	//SDL_GL_LoadLibrary(NULL);
	//// Request an OpenGL 4.5 context (should be core)
	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	//// Also request a depth buffer
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#ifdef _WIN32
	m_pSDLWindow = SDL_CreateWindow("Construct (SDL2)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
#else
	//Get device display mode
	SDL_Rect gScreenRect = { 0, 0, 320, 240 };
	SDL_DisplayMode displayMode;
	if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
	{
		gScreenRect.w = displayMode.w;
		gScreenRect.h = displayMode.h;
	}

	//Create window
	m_pSDLWindow = SDL_CreateWindow( "Construct (SDL2)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN );

//	if( m_pSDLWindow == NULL )
//	{
//		SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
//	} else{
//		SDL_Log("Eeee dayi?");
//	}
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
 //   SDL_Log("CSDLWindow::onUpdate()");

	//Handle events on queue
	while (SDL_PollEvent(&m_SDLEvent) != 0)
	{
		handleEvent(m_SDLEvent);
	}

//	int x, y;
//	SDL_GetMouseState(&x, &y);
//
//	std::string testString;
//	testString = "X: " + std::to_string(x) + " Y: " + std::to_string(y);
//	SDL_SetWindowTitle(m_pSDLWindow, testString.c_str());
	//GetSystem()->GetLogger()->Log(testString.c_str());
	//SDL_GL_SwapWindow(m_pSDLWindow);
}

/////////////////////////////////////////////////
void CSDLWindow::handleEvent(const SDL_Event & SDLEvent)
{
    SDL_Log("CSDLWindow::handleEvent()");

	switch (SDLEvent.type)
	{
	case SDL_QUIT:
	{
		m_quit = true;
	}
	break;
	//case SDL_KEYDOWN:
	//{
	//	SWindowEvent windowEvent;
	//	windowEvent.event_type = EWindowEventType::eWE_KEY_PRESSED;
	//	windowEvent.scancode = SDLEvent.key.keysym.scancode;
	//	m_callbackFn(windowEvent);
	//	GetSystem()->GetLogger()->Log("SDL_KEYDOWN");
	//}
	//break;
	//case SDL_KEYUP:
	//{
	//	SWindowEvent windowEvent;
	//	windowEvent.event_type = EWindowEventType::eWE_KEY_RELEASED;
	//	windowEvent.scancode = SDLEvent.key.keysym.scancode;
	//	m_callbackFn(windowEvent);
	//	GetSystem()->GetLogger()->Log("SDL_KEYUP");
	//}
	//break;
	//case SDL_MOUSEMOTION:
	//{
	//	SWindowEvent windowEvent;
	//	windowEvent.event_type = EWindowEventType::eWE_MOUSE_POSITION_CHANGED;
	//	windowEvent.x = SDLEvent.motion.x;
	//	windowEvent.y = SDLEvent.motion.y;
	//	m_callbackFn(windowEvent);
	//	//GetSystem()->GetLogger()->Log("SDL_MOUSEMOTION");
	//	std::string testString;
	//	testString = "X: " + std::to_string(windowEvent.x) + " Y: " + std::to_string(windowEvent.y);
	//	SDL_SetWindowTitle(m_pSDLWindow, testString.c_str());
	//}
	//break;
	//case SDL_MOUSEBUTTONDOWN:
	//{
	//	SWindowEvent windowEvent;
	//	windowEvent.event_type = EWindowEventType::eWE_MOUSE_BUTTON_PRESSED;
	//	windowEvent.scancode = SDLEvent.button.button;
	//	m_callbackFn(windowEvent);
	//	GetSystem()->GetLogger()->Log("SDL_MOUSEBUTTONDOWN");
	//}
	//break;
	//case SDL_MOUSEBUTTONUP:
	//{
	//	SWindowEvent windowEvent;
	//	windowEvent.event_type = EWindowEventType::eWE_MOUSE_BUTTON_RELEASED;
	//	windowEvent.scancode = SDLEvent.button.button;
	//	m_callbackFn(windowEvent);
	//	GetSystem()->GetLogger()->Log("SDL_MOUSEBUTTONUP");
	//}
	//break;
	}
}
