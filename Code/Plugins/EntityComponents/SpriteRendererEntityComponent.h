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
	
private:
	void onEntityUpdateEvent();
	void onEntityDestroyEvent();

private:
	float m_width;
	float m_height;
	ISprite* m_pSprite;
	std::string m_spriteFile;
	SSpriteParams::SSpriteScrollParams m_scrollParams;
	int m_layerId = -1;
};