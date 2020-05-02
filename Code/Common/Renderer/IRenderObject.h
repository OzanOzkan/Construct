#pragma once

#include "../Math/Math.h"

#include <string>
#include <vector>

typedef struct RGBAColor
{
	RGBAColor(const uint8_t& R, const uint8_t& G, const uint8_t& B, const uint8_t& A) noexcept
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
	virtual void Load(const SRenderObjectParams& params) = 0;
	virtual void RenderCopy() = 0;

	void setId(const int& id) noexcept { m_id = id; }
	const int& getId() noexcept { return m_id; }
	void setLayerId(const int& layerId) noexcept { m_layerId = layerId; }
	const int& getLayerId() noexcept { return m_layerId; }
	void setPosition(const Vector2& position) noexcept { m_position = position; }
	const Vector2& getPosition() noexcept { return m_position; }
	void setRotation(const float& rotation) noexcept { m_rotation = rotation; }
	float getRotation() noexcept { return m_rotation; }
	void setSize(const float& w, const float& h) noexcept { m_width = w; m_height = h; }
	void setColor(const RGBAColor& color) noexcept { m_color = color; }
	RGBAColor getColor() noexcept { return m_color; }
	ERendererObjectType getType() noexcept { return m_type; }
	void setType(ERendererObjectType type) noexcept { m_type = type; }
	void setRenderActive(const bool& isRenderActive) noexcept { m_isRenderActive = isRenderActive; }
	bool isRenderActive() noexcept { return m_isRenderActive; }

	const float& getWidth() const noexcept { return m_width; }
	const float& getHeight() const noexcept { return m_height; }

	void setDebugDraw(const bool& isActive) noexcept { m_debugDraw = isActive; }
	
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
	SRectParams() noexcept { type = ERendererObjectType::eRT_RECT; }
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

	SSpriteParams() noexcept { type = ERendererObjectType::eRT_SPRITE; }

	std::string spriteFile{};
	SSpriteScrollParams scrollParams;
};

class ISprite : public IRendererObject
{
public:
	virtual void setFile(const std::string& file) = 0;

protected:
	std::string m_file;
};
/////////// ~Sprite

/////////// Animated Sprite
struct SAnimatedSpriteParams : public SRenderObjectParams
{
	SAnimatedSpriteParams() noexcept { type = ERendererObjectType::eRT_ANIMATED_SPRITE; }

public:
	void addFrameFile(const std::string& frameFile)
	{
		m_frameFiles.emplace_back(frameFile);
	}

	std::vector<std::string>& getFrameFiles() noexcept
	{ 
		return m_frameFiles;
	}

	const std::vector<std::string>& getFrameFiles() const noexcept
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
	STextParams() noexcept { type = ERendererObjectType::eRT_TEXT; }

	std::string text;
	std::string font;
	int fontSize = -1;
};

class IText : public IRendererObject
{
public:
	void setText(const std::string& text) { m_text = text; }
	const std::string& getText() noexcept { return m_text; }

	void setFont(const std::string& font) { m_font = font; }
	const std::string& getFont() noexcept { return m_font; }

	void setFontSize(const int& fontSize) noexcept { m_fontSize = fontSize; }
	const int& getFontSize() noexcept { return m_fontSize; }

protected:
	std::string m_text;
	std::string m_font;
	int m_fontSize;
};
/////////// ~Text