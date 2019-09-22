#pragma once

#include <System/ISystem.h>
#include <System/IWindow.h>
#include <System/IWindowEventListener.h>

#include <SDL.h>

class CSDLWindow : public IWindow
{
public:
	CSDLWindow(SEnvironment* env);
	virtual ~CSDLWindow();

	// IWindow
	virtual void openWindow(const int& height, const int& width, TEventCallbackFn callbackFn) override;
	virtual WindowProcAddr getWindowProcAddress() override { return (WindowProcAddr)SDL_GL_GetProcAddress; }
	virtual void closeWindow() override;
	virtual void onUpdate() override;
	TEventCallbackFn GetCallbackFunction() { return m_callbackFn; }
	// ~IWindow

private:
	SEnvironment * m_pEnv = nullptr;
	TEventCallbackFn m_callbackFn;
	bool m_quit = false;
	SDL_Window * m_pSDLWindow = nullptr;
	SDL_Surface * m_pSDLSurface = nullptr;
	SDL_Event m_SDLEvent;

	int m_height;
	int m_width;
};