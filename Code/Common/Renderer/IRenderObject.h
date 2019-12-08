#pragma once

#include <string>

enum class ERendererObjectType
{
	eRT_NONE = 0,
	eRT_SPRITE,
	eRT_TEXT
};

struct SRenderObjectCreateParams
{
	virtual ~SRenderObjectCreateParams() {}

	float posX = -1;
	float posY = -1;
	float width = -1;
	float height = -1;
	ERendererObjectType type = ERendererObjectType::eRT_NONE;
};

class IRendererObject
{
public:
	virtual ~IRendererObject() {}
	
	virtual void Load(const SRenderObjectCreateParams& params) = 0;
	virtual void RenderCopy() = 0;

	void setId(const int& id) { m_id = id; }
	const int& getId() { return m_id; }
	void setPosition(const float& x, const float& y) { m_posX = x; m_posY = y; }
	void setSize(const float& w, const float& h) { m_width = w; m_height = h; }
	ERendererObjectType getType() { return m_type; }
	void setType(ERendererObjectType type) { m_type = type; }
	void setRenderActive(const bool& isRenderActive) { m_isRenderActive = isRenderActive; }
	const bool& isRenderActive() { return m_isRenderActive; }

	const float& getPosX() const { return m_posX; }
	const float& getPosY() const { return m_posY; }

	const float& getWidth() const { return m_width; }
	const float& getHeight() const { return m_height; }
	
protected:
	int m_id = -1;
	ERendererObjectType m_type;
	bool m_isRenderActive = false;
	float m_posX = -1;
	float m_posY = -1;
	float m_width = -1;
	float m_height = -1;
};

/////////// Sprite
struct SSpriteCreateParams : public SRenderObjectCreateParams
{
	SSpriteCreateParams() { type = ERendererObjectType::eRT_SPRITE; }

	std::string spriteFile = "";
};

class ISprite : public IRendererObject
{
public:
	virtual void setFile(const std::string& file) = 0;

protected:
	std::string m_file {};
};
/////////// ~Sprite

/////////// Text
struct STextCreateParams : public SRenderObjectCreateParams
{
	STextCreateParams() { type = ERendererObjectType::eRT_TEXT; }

	std::string text = "";
	std::string font = "";
	int fontSize = -1;
};

class IText : public IRendererObject
{
public:
	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() { return m_text; }

	void setFont(const std::string& font) { m_font = font; }
	const std::string& getFont() { return m_font; }

	void setFontSize(const int& fontSize) { m_fontSize = fontSize; }
	const int& getFontSize() { return m_fontSize; }

protected:
	std::string m_text;
	std::string m_font;
	int m_fontSize;
};
/////////// ~Text