#pragma once

#include <System/ISystem.h>
#include <System/EntitySystem/IEntityComponent.h>

class MainMenuButtonController : public IEntityComponent
{
public:
	void Init() override;
	unsigned int getEventMask() const override { return 0; }
	void onEvent(const SEntityEvent& event) override {}
	void updateComponent() override {}

	void getClassDesc(std::map<std::string, void*>& desc) {
		desc.emplace("levelToLoad", &m_levelToLoad);
	}

private:
	std::string m_levelToLoad;
};

REGISTER_ENTITY_COMPONENT(MainMenuButtonController);