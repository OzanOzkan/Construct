#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderObject.h>

class SpriteRendererEntityComponent : public IEntityComponent
{
public:
	SpriteRendererEntityComponent();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const EEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

	void setFile(const std::string& file) { m_spriteFile = file; }
	void setSize(const float& height, const float& width);
	void onEntityUpdate();

private:
	std::string m_spriteFile;
	float m_height;
	float m_width;
	ISprite* m_pSprite;
};