#pragma once

#include <System/EntitySystem/IEntityComponent.h>

class SpriteRendererEntityComponent : public IEntityComponent
{
public:
	virtual ~SpriteRendererEntityComponent() {}

	// IEntityComponent
	virtual unsigned int getEventMask() const override;
	virtual void onEvent(const EEntityEvent& event) override;
	// ~IEntityComponent

	void setFile(const std::string& file) { m_spriteFile = file; }
	void onEntityUpdate();

private:
	std::string m_spriteFile = "";
};