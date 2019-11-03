#pragma once

#include <string>

enum class ERendererObjectType
{
	eRT_NONE = 0,
	eRT_SPRITE
};

class IRendererObject
{
public:
	virtual ~IRendererObject() {}
	
	virtual void Load() = 0;
	void setId(const int& id) { m_id = id; }
	const int& getId() { return m_id; }
	void setPosition(const float& x, const float& y) { m_posX = x; m_posY = y; }
	ERendererObjectType getType() { return m_type; }
	void setType(ERendererObjectType type) { m_type = type; }
	void setRenderActive(const bool& isRenderActive) { m_isRenderActive = isRenderActive; }
	const bool& isRenderActive() { return m_isRenderActive; }

	const float& getPosX() const { return m_posX; }
	const float& getPosY() const { return m_posY; }
	
protected:
	int m_id = -1;
	ERendererObjectType m_type;
	bool m_isRenderActive = false;
	float m_posX = -1;
	float m_posY = -1;
};

/////////// Sprite
struct SSpriteCreateParams
{
	std::string spriteFile = "";
	float w = -1;
	float h = -1;
	float posX = -1;
	float posY = -1;
};

class ISprite : public IRendererObject
{
public:
	virtual ~ISprite() {}

	virtual void setFile(const std::string& file) = 0;
	virtual void setSize(const float& w, const float& h) = 0;
	virtual const int& getTextureId() const = 0;

	virtual const float& getWidth() const { return m_width; }
	virtual const float& getHeight() const { return m_height; }

protected:
	std::string m_file {};
	int m_textureId = -1;
	float m_width = -1;
	float m_height = -1;
};
/////////// ~Sprite