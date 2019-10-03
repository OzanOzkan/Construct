/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <IModule.h>
#include <System/ISystem.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntityComponent.h>

/*
	SUBJECT TO CHANGE: All of the Game module implementation is temporary.
*/

class CMyEntityComponent : public IEntityComponent
{
public:
	CMyEntityComponent() {};
	
	bool testComponent() { return true; }
};


class CGame : public IModule
{
public:
	CGame(SEnvironment* env);
	virtual ~CGame() {}

	virtual void InitializeModule() override;
	virtual void onUpdate() override {}

private:
	SEnvironment * m_pEnv = nullptr;
};