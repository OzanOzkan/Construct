#pragma once

#include <System/EntitySystem/IEntityComponent.h>

class CSideScrollerLevelController : public IEntityComponent 
{
public:
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	
private:
	void setupLevel();
};

REGISTER_ENTITY_COMPONENT(CSideScrollerLevelController);