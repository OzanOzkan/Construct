#pragma once

#include <System/ISystem.h>
#include <ILog.h>

#include "../ILevel.h"

class CNebula : public ILevel
{
public:
	CNebula(ISystem* systemContext);

	// ILevel
	void loadLevel() override;
	// ~ILevel

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
};