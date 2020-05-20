#include <Physics/IPhysics.h>
#include "B2DPhysics/B2DPhysics.h"

extern "C"
{
	API_EXPORT IPhysics* CreateModuleInterface(ISystem* systemContext, SCreateModuleParams<EPhysics> createParams)
	{
		IPhysics* pPhysics = nullptr;

		switch(createParams.implType)
		{
		case EPhysics::BOX2D:
		{
			pPhysics = new CB2DPhysics(systemContext);
		}
		break;
		}

		pPhysics->InitializeModule();

		return pPhysics;
	}
}