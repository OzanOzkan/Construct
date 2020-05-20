#include "SideScrollerPlayerController.h"

#include <System/EntitySystem/IEntity.h>
#include <Renderer/IRenderer.h>

/////////////////////////////////////////////////
CSideScrollerPlayerController::CSideScrollerPlayerController()
	: m_pInput(nullptr)
	, m_pRigidBodyComponent(nullptr)
{
}

/////////////////////////////////////////////////
void CSideScrollerPlayerController::Init()
{
	m_pInput = GetSystem()->GetInput();
}

/////////////////////////////////////////////////
unsigned int CSideScrollerPlayerController::getEventMask() const
{
	return ENTITY_EVENT_UPDATE | ENTITY_LEVEL_LOAD_END;
}

/////////////////////////////////////////////////
void CSideScrollerPlayerController::onEvent(const SEntityEvent& event)
{
	if (event.GetEvent() == ENTITY_EVENT_UPDATE) {
		processInput();
		updateCamera();
	}
	else if (event.GetEvent() == ENTITY_LEVEL_LOAD_END) {
		m_pRigidBodyComponent = getEntity()->getEntityComponent<Rigidbody2D>();
	}
}

/////////////////////////////////////////////////
void CSideScrollerPlayerController::updateComponent()
{
}

/////////////////////////////////////////////////
void CSideScrollerPlayerController::processInput()
{
	if (m_pInput->IsKeyPressed(EKey::eKID_SPACE)) {
		m_pRigidBodyComponent->applyLinearImpulse(Vector2(0.f, -1.f));
	}
	else if (m_pInput->IsKeyPressed(EKey::eKID_A)) {
		getEntity()->setPosition(getEntity()->getPosition() - (Vector2(300, 0) * GetSystem()->GetTime()->GetDeltaTime()));
	}
	else if (m_pInput->IsKeyPressed(EKey::eKID_D)) {
		getEntity()->setPosition(getEntity()->getPosition() + (Vector2(300, 0) * GetSystem()->GetTime()->GetDeltaTime()));
	}
}

void CSideScrollerPlayerController::updateCamera()
{
	Vector2 playerCenteredHWCameraPos(getEntity()->getPosition() + Vector2(500, 1500));
	Vector2 playerCenteredHCameraPos((getEntity()->getPosition().x * -1) + 500, GetSystem()->GetRenderer()->GetCamera()->GetPosition().y);

	GetSystem()->GetRenderer()->GetCamera()->SetPosition(playerCenteredHCameraPos);
}
