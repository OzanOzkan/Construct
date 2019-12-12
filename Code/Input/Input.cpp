/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "SDLInput/SDLInput.h"
#include <ILog.h>

extern "C"
{
	API_EXPORT IInput* CreateInputInterface(ISystem* systemContext, EInput inputImplementation)
	{
		IInput* pInput = nullptr;

		switch (inputImplementation)
		{
		case EInput::eINP_SDL2:
		{
			pInput = new CSDLInput(systemContext);
		}
		break;
		}

		pInput->InitializeModule();

		return pInput;
	}
}