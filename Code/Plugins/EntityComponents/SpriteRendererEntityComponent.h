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
	void setScrollParams(const SSpriteParams::SSpriteScrollParams& scrollParams) { m_scrollParams = scrollParams; }
	void setLayerId(const int& layerId) { m_layerId = layerId; }
	void setDebugDraw(const bool& isActive);
	
private:
	void onEntityUpdateEvent();
	void onEntityDestroyEvent();
	void DebugDraw();

private:
	float m_width;
	float m_height;
	ISprite* m_pSprite;
	std::string m_spriteFile;
	SSpriteParams::SSpriteScrollParams m_scrollParams;
	int m_layerId = -1;

	bool m_debugDraw = false;
	IRect* m_pDebugRect = nullptr;
	IText* m_pDebugText = nullptr;
};