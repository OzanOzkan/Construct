#pragma once

#include "../Math/Math.h"

#include <string>
#include <vector>

typedef struct RGBAColor
{
	RGBAColor(const uint8_t& R, const uint8_t& G, const uint8_t& B, const uint8_t& A)
		: r(R), g(G), b(B), a(A)
	{}

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} RGBAColor;

enum class ERendererObjectType
{
	eRT_NONE = 0,
	eRT_RECT,
	eRT_SPRITE,
	eRT_ANIMATED_SPRITE,
	eRT_TEXT
};

enum class ERenderObjectClass
{
	NONE = 0,
	WORLD,
	UI
};

struct SRenderObjectParams
{
	virtual ~SRenderObjectParams() {}
	
	int layerId = 0;
	Vector2 position{ -1.f, -1.f };
	float rotation = 0;
	float width = -1;
	float height = -1;
	RGBAColor color = { 0,0,0,1 };
	ERendererObjectType type = ERendererObjectType::eRT_NONE;
	ERenderObjectClass renderObjectClass = ERenderObjectClass::NONE;
};

class IRendererObject
{
public:
	virtual ~IRendererObject() {}
	
	virtual void Load(const SRenderObjectParams& params) = 0;
	virtual void RenderCopy() = 0;

	void setId(const int& id) { m_id = id; }
	const int& getId() { return m_id; }
	void setLayerId(const int& layerId) { m_layerId = layerId; }
	const int& getLayerId() { return m_layerId; }
	void setPosition(const Vector2& position) { m_position = position; }
	const Vector2& getPosition() { return m_position; }
	void setRotation(const float& rotation) { m_rotation = rotation; }
	float getRotation() { return m_rotation; }
	void setSize(const float& w, const float& h) { m_width = w; m_height = h; }
	void setColor(const RGBAColor& color) { m_color = color; }
	RGBAColor getColor() { return m_color; }
	ERendererObjectType getType() { return m_type; }
	void setType(ERendererObjectType type) { m_type = type; }
	void setRenderActive(const bool& isRenderActive) { m_isRenderActive = isRenderActive; }
	bool isRenderActive() { return m_isRenderActive; }

	const float& getWidth() const { return m_width; }
	const float& getHeight() const { return m_height; }

	void setDebugDraw(const bool& isActive) { m_debugDraw = isActive; }
	
protected:
	int m_id = -1;
	int m_layerId = -1;
	ERendererObjectType m_type;
	ERenderObjectClass m_class;
	bool m_isRenderActive = true;
	Vector2 m_position { 0.f, 0.f };
	float m_rotation = 0;
	float m_width = -1;
	float m_height = -1;
	bool m_debugDraw = false;
	RGBAColor m_color = { 0,0,0,1 };
};

/////////// Rect
struct SRectParams : public SRenderObjectParams
{
	SRectParams() { type = ERendererObjectType::eRT_RECT; }
};

class IRect : public IRendererObject
{
	
};
/////////// ~Rect

/////////// Sprite
struct SSpriteParams : public SRenderObjectParams
{
	struct SSpriteScrollParams
	{
		enum class ESpriteScrollDirection
		{
			eSPD_NONE = 0,
			eSPD_UP,
			eSPD_DOWN,
			eSPD_LEFT,
			eSPR_RIGHT
		};

		ESpriteScrollDirection scrollDirection = ESpriteScrollDirection::eSPD_NONE;
		float scrollSpeed = -1;
	};

	SSpriteParams() { type = ERendererObjectType::eRT_SPRITE; }

	std::string spriteFile = "";
	SSpriteScrollParams scrollParams;
};

class ISprite : public IRendererObject
{
public:
	virtual void setFile(const std::string& file) = 0;

protected:
	std::string m_file {};
};
/////////// ~Sprite

/////////// Animated Sprite
struct SAnimatedSpriteParams : public SRenderObjectParams
{
	SAnimatedSpriteParams() { type = ERendererObjectType::eRT_ANIMATED_SPRITE; }

public:
	void addFrameFile(const std::string& frameFile)
	{
		m_frameFiles.emplace_back(frameFile);
	}

	std::vector<std::string>& getFrameFiles()
	{
		return m_frameFiles;
	}

	const std::vector<std::string>& getFrameFiles() const
	{
		return m_frameFiles;
	}

	int animationSpeed = 1;

private:
	std::vector<std::string> m_frameFiles;
};

class IAnimatedSprite : public IRendererObject
{
public:
	virtual int getFrameCount() = 0;
	virtual int getCurrentFrame() = 0;
	virtual void setAnimationSpeed(const int& speed) = 0;
};
/////////// ~Animated Sprite

/////////// Text
struct STextParams : public SRenderObjectParams
{
	STextParams() { type = ERendererObjectType::eRT_TEXT; }

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