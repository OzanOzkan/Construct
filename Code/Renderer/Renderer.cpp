#include <System/ISystem.h>
#include <ILog.h>
#include <string>

#include "SDLRenderer/SDLRenderer.h"

/////////////////////////////////////////////////
extern "C"
{
	API_EXPORT IRenderer* CreateModuleInterface(ISystem * systemContext, SCreateModuleParams<ERenderer> createParams)
	{
		IRenderer* pRenderer = nullptr;

		switch (createParams.implType)
		{
		case ERenderer::SDL2:
		{
			pRenderer = new CSDLRenderer(systemContext);
		}
		break;
		}

		pRenderer->InitializeModule();

		return pRenderer;
	}
}