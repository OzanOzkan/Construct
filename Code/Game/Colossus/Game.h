#pragma once

#include <IGame.h>
#include <System/ISystem.h>
#include <ILog.h>

class CGame : public IGame
{
public:
	CGame(ISystem* systemContext) noexcept;
	~CGame() {}

	void InitializeModule() override;

	void onPreUpdate() override {}
	void onUpdate() override;
	void onPostUpdate() override {}

private:
	ISystem * GetSystem() noexcept { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
};