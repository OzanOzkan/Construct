#pragma once

#include "Window.h"
#include <SDL.h>

class CSDLWindow : public CWindow
{
public:
	CSDLWindow(ISystem* systemContext);

	// CWindow
	void openWindow(const int& height, const int& width, TEventCallbackFn callbackFn, void* renderTarget) override;
	int getWindowId() override { return SDL_GetWindowID(m_pSDLWindow); }
	void closeWindow() override;
	void onUpdate() override;
	int getTicks() override { return SDL_GetTicks(); }
	void setWindowSize(const int& width, const int& height) override;
	// ~CWindow

private:
	void handleEvent(const SDL_Event& SDLEvent);

private:
	SDL_Window* m_pSDLWindow;
	SDL_Surface* m_pSDLSurface;
	SDL_Event m_SDLEvent;
};