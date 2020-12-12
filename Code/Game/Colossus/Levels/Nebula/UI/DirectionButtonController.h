#pragma once

#include <System/EntitySystem/IEntityComponent.h>

class CDirectionButtonController : public IEntityComponent
{
public:
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;

	void getClassDesc(std::map<std::string, void*>& desc) {
		desc.emplace("direction", &m_direction);
	}

private:
	void setupButton();

private:
	std::string m_direction;
};

REGISTER_ENTITY_COMPONENT(CDirectionButtonController);