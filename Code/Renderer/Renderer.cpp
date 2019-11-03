/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include <System/ISystem.h>
#include <ILog.h>
#include <string>

#include "SDLRenderer/SDLRenderer.h"

/////////////////////////////////////////////////
extern "C"
{
	API_EXPORT IRenderer* CreateModuleInterface(SEnvironment *env, ERenderer renderer)
	{
		IRenderer* pRenderer = nullptr;

		switch (renderer)
		{
		case ERenderer::eRDR_SDL2:
		{
			pRenderer = new CSDLRenderer(env);
		}
		break;
		}

		pRenderer->InitializeModule();

		return std::move(pRenderer);
	}
}