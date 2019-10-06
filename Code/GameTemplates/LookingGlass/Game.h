/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once
#include <IModule.h>
#include <System/ISystem.h>
#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntityComponent.h>
#include <ILog.h>

/*
	SUBJECT TO CHANGE: All of the Game module implementation is temporary.
*/

//class CMyEntityComponent : public IEntityComponent
//{
//public:
//	virtual ~CMyEntityComponent() {}
//
//	virtual unsigned int getEventMask() const override 
//	{ 
//		return EEntityEvent::ENTITY_EVENT_INIT | EEntityEvent::ENTITY_EVENT_UPDATE; 
//	}
//
//	virtual void onEvent(const EEntityEvent& event) override
//	{
//		static int test = 0;
//
//		switch (event)
//		{
//		case EEntityEvent::ENTITY_EVENT_INIT:
//		{
//			test = 1;
//		}
//		break;
//		case EEntityEvent::ENTITY_EVENT_UPDATE:
//		{
//			test = 2;
//		}
//		break;
//		}
//	}
//
//	bool testComponent() { return true; }
//};


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