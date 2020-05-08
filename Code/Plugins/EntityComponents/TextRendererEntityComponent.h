#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderObject.h>

class TextRendererEntityComponent : public IEntityComponent
{
public:
	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

	void getClassDesc(std::map<std::string, void*>& desc) {
		desc.emplace("text", &m_text);
		desc.emplace("fontSize", &m_fontSize);
		desc.emplace("layerId", &m_layerId);
		desc.emplace("color", &m_color.r);
	}

	void setText(const std::string& text) { m_text = text; }
	void setFont(const std::string& font) { m_font = font; }
	void setFontSize(const int& size) noexcept { m_fontSize = size; }
	void setLayerId(const int& layerId) noexcept { m_layerId = layerId; }
	void setColor(const RGBAColor& color) noexcept { m_color = color; }

private:
	void onEntityUpdateEvent();
	void onEntityDestroyEvent();

private:
	std::string m_text = "";
	std::string m_font = "";
	int m_fontSize = -1;
	IText* m_pText = nullptr;
	int m_layerId = -1;
	RGBAColor m_color = { 255,255,255,1 };
};

REGISTER_ENTITY_COMPONENT(TextRendererEntityComponent);