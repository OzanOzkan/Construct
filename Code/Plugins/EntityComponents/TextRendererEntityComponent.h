#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderObject.h>

class TextRendererEntityComponent : public IEntityComponent
{
public:
	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const EEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

	void setText(const std::string& text) { m_text = text; }
	void setFont(const std::string& font) { m_font = font; }
	void setFontSize(const int& size) { m_fontSize = size; }

private:
	void onEntityUpdateEvent();
	void onEntityDestroyEvent();

private:
	std::string m_text = "";
	std::string m_font = "";
	int m_fontSize = -1;
	IText* m_pText = nullptr;
};