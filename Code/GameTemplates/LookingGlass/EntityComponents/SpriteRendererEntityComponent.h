#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderObject.h>

class SpriteRendererEntityComponent : public IEntityComponent
{
public:
	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const EEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

	void setFile(const std::string& file) { m_spriteFile = file; }
	void onEntityUpdate();

private:
	std::string m_spriteFile = "";
	float m_width = -1;
	float m_height = -1;

	ISprite* m_pSprite = nullptr;
};