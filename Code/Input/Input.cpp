/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "SDLInput/SDLInput.h"
#include <ILog.h>

extern "C"
{
	API_EXPORT IInput* CreateModuleInterface(ISystem* systemContext, SCreateModuleParams<EInput> createParams)
	{
		IInput* pInput = nullptr;

		switch (createParams.implType)
		{
		case EInput::SDL2:
		{
			pInput = new CSDLInput(systemContext);
		}
		break;
		}

		pInput->InitializeModule();

		return pInput;
	}
}