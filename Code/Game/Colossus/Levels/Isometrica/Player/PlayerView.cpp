/* Copyright (C) 2020 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "PlayerView.h"

#include <System/EntitySystem/IEntity.h>
#include <IInput.h>
#include <ILog.h>
#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
CPlayerView::CPlayerView()
{

}

/////////////////////////////////////////////////
void CPlayerView::Init()
{

}

/////////////////////////////////////////////////
unsigned int CPlayerView::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE;
}

/////////////////////////////////////////////////
void CPlayerView::onEvent(const SEntityEvent & event)
{
	ICamera* pCamera = GetSystem()->GetRenderer()->GetCamera();

	// Control camera with touch input.
	static bool firstTouch = true;
	static Vector2 lastPos(0, 0);
	STouchEventList touchEvents = GetSystem()->GetInput()->GetTouchEvents();
	Vector2 inputPos = !touchEvents.empty() ? touchEvents.front().position
		: GetSystem()->GetInput()->GetMousePosition();

	if (!touchEvents.empty() || GetSystem()->GetInput()->IsKeyPressed(EKey::eKID_MOUSE_LEFT))
	{		
		if (firstTouch)
		{
			lastPos = inputPos;
			firstTouch = false;
		}
		else
		{
			Vector2 offset = lastPos - inputPos;
			Vector2 movePos = Vector2(offset.x * -1.2, offset.y * -1.2);
			pCamera->SetPosition(pCamera->GetPosition() + movePos);

			lastPos = inputPos;
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
void CPlayerView::updateComponent()
{

}
