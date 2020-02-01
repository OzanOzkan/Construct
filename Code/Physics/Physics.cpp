/* Copyright (C) 2020 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include <Physics/IPhysics.h>
#include "SDLPhysics/SDLPhysics.h"

extern "C"
{
	API_EXPORT IPhysics* CreatePhysicsInterface(ISystem* systemContext)
	{
		IPhysics* pPhysics = new CSDLPhysics(systemContext);

		pPhysics->InitializeModule();

		return pPhysics;
	}
}