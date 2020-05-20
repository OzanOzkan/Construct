#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <IInput.h>
#include <EntityComponents/Physics/Rigidbody2D.h>

class CSideScrollerPlayerController : public IEntityComponent
{
public:
	CSideScrollerPlayerController();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

private:
	void processInput();
	void updateCamera();

private:
	IInput* m_pInput;
	Rigidbody2D* m_pRigidBodyComponent;
};

REGISTER_ENTITY_COMPONENT(CSideScrollerPlayerController);