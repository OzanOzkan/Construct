/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "Window.h"
#include <SDL.h>

class CSDLWindow : public CWindow
{
public:
	CSDLWindow(ISystem* systemContext);

	// CWindow
	void openWindow(const int& height, const int& width, TEventCallbackFn callbackFn) override;
	int getWindowId() override { return SDL_GetWindowID(m_pSDLWindow); }
	void closeWindow() override;
	void onUpdate() override;
	int getTicks() override { return SDL_GetTicks(); }
	// ~CWindow

private:
	void handleEvent(const SDL_Event& SDLEvent);

private:
	SDL_Window * m_pSDLWindow = nullptr;
	SDL_Surface * m_pSDLSurface = nullptr;
	SDL_Event m_SDLEvent;
};