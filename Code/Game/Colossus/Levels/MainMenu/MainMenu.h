#pragma once

#include <System/ISystem.h>
#include "../ILevel.h"

class CMainMenu : public ILevel
{
public:
	CMainMenu(ISystem* systemContext);

	// ILevel
	void loadLevel() override;
	// ~ILevel

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
};