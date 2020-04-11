#pragma once

#include <System/ISystem.h>
#include <ILog.h>
#include "../ILevel.h"

class CIsometrica : public ILevel
{
public:
	CIsometrica(ISystem* systemContext);

	// ILevel
	void loadLevel() override;
	// ~ILevel

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
};