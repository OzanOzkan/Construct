#include "PhysicalizedObjectController.h"

#include <System/EntitySystem/IEntitySystem.h>
#include <System/EntitySystem/IEntity.h>
#include <EntityComponents/OnSelectionListenerEntityComponent.h>
#include <EntityComponents/Physics/Rigidbody2D.h>

/////////////////////////////////////////////////
void CPhysicalizedObjectController::Init()
{
}

/////////////////////////////////////////////////
unsigned int CPhysicalizedObjectController::getEventMask() const
{
	return ENTITY_LEVEL_LOAD_END;
}

/////////////////////////////////////////////////
void CPhysicalizedObjectController::onEvent(const SEntityEvent& event)
{
	if (event.GetEvent() == ENTITY_LEVEL_LOAD_END) {
		setupOnSelectionAction();
	}
}

/////////////////////////////////////////////////
void CPhysicalizedObjectController::updateComponent()
{
}

/////////////////////////////////////////////////
void CPhysicalizedObjectController::setupOnSelectionAction()
{
	if (OnSelectionListenerEntityComponent* pSelectionComponent =
		getEntity()->getEntityComponent<OnSelectionListenerEntityComponent>()) {
		pSelectionComponent->subscribeOnSelection([this](const bool& isSelected, const Vector2& selectionPos) {
			if (isSelected) {
				if (Rigidbody2D* pRigidbodyComponent = getEntity()->getEntityComponent<Rigidbody2D>()) {
					pRigidbodyComponent->applyLinearImpulse(Vector2(0, -0.1f));
				}
			}
			});
	}
}
