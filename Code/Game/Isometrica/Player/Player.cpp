/* Copyright (C) 2020 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Player.h"

#include <System/EntitySystem/IEntity.h>
#include <IInput.h>
#include <ILog.h>
#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
CPlayer::CPlayer()
{

}

/////////////////////////////////////////////////
void CPlayer::Init()
{

}

/////////////////////////////////////////////////
unsigned int CPlayer::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void CPlayer::onEvent(const SEntityEvent & event)
{
	ICamera* pCamera = GetSystem()->GetRenderer()->GetCamera();

	// Control camera with touch input.
	static bool firstTouch = true;
	STouchEventList touchEvents = GetSystem()->GetInput()->GetTouchEvents();
	if (!touchEvents.empty())
	{
		STouchEvent touchEvent = touchEvents.front();
		static Vector2 lastPos;
		if (firstTouch)
		{
			lastPos = touchEvent.position;
			firstTouch = false;
		}
		else
		{
			Vector2 offset = lastPos - touchEvent.position;
			Vector2 movePos = Vector2(offset.x * 1.2, offset.y * 1.2);
			pCamera->SetPosition(pCamera->GetPosition() + movePos);

			lastPos = touchEvent.position;
		}
	}
	else
	{
		firstTouch = true;
	}

	// Control camera with keyboard input.
	if (GetSystem()->GetInput()->IsKeyPressed(EKey::eKID_A))
		pCamera->SetPosition(pCamera->GetPosition() + Vector2(50, 0));
	if (GetSystem()->GetInput()->IsKeyPressed(EKey::eKID_D))
		pCamera->SetPosition(pCamera->GetPosition() + Vector2(-50, 0));
	if (GetSystem()->GetInput()->IsKeyPressed(EKey::eKID_W))
		pCamera->SetPosition(pCamera->GetPosition() + Vector2(0, 50));
	if (GetSystem()->GetInput()->IsKeyPressed(EKey::eKID_S))
		pCamera->SetPosition(pCamera->GetPosition() + Vector2(0, -50));

}

/////////////////////////////////////////////////
void CPlayer::updateComponent()
{

}
