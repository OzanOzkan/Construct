#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderer.h>
#include <Renderer/IRenderObject.h>

class SpriteRendererEntityComponent : public IEntityComponent
{
public:
	SpriteRendererEntityComponent();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

	void setFile(const std::string& file);
	void setSize(const float& height, const float& width);
	void getSize(float& height, float& width);
	void setColor(const RGBAColor& color);
	void setScrollParams(const SSpriteParams::SSpriteScrollParams& scrollParams) noexcept { m_scrollParams = scrollParams; }
	void setLayerId(const int& layerId) noexcept { m_layerId = layerId; }
	void setDebugDraw(const bool& isActive);
	
private:
	void onEntityUpdateEvent();
	void onEntityDestroyEvent();
	void DebugDraw();

private:
	float m_width = -1;
	float m_height = -1;
	RGBAColor m_color;
	ISprite* m_pSprite;
	std::string m_spriteFile;
	SSpriteParams::SSpriteScrollParams m_scrollParams;
	int m_layerId = -1;

	bool m_debugDraw = false;
	IRect* m_pDebugRect = nullptr;
	IText* m_pDebugText = nullptr;
};

REGISTER_ENTITY_COMPONENT(SpriteRendererEntityComponent);