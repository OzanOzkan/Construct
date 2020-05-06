#pragma once

#include <IGame.h>
#include <System/ISystem.h>
#include <ILog.h>

/*
	SUBJECT TO CHANGE: All of the Game module implementation is temporary.
*/

class CGame : public IGame
{
public:
	CGame(ISystem* systemContext) noexcept;
	~CGame() {}

	void InitializeModule() override;
	void onUpdate() override;

private:
	ISystem * GetSystem() noexcept { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
};