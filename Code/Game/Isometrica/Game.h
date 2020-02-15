/* Copyright (C) 2020 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

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
	CGame(ISystem* systemContext);

	void InitializeModule() override;
	void onUpdate() override {}

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem = nullptr;
};