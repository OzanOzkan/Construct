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
	void onUpdate() override;
	// ~ILevel

private:
	ISystem * GetSystem() noexcept { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
};