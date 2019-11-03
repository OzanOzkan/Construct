#pragma once

#include <Renderer/IRenderObject.h>

class IRenderer;

class CSprite : public ISprite
{
public:
	CSprite(IRenderer* pRendererContext);
	virtual ~CSprite() {}

	virtual void Load() override;
	virtual void setFile(const std::string& file) override;
	virtual void setSize(const float& w, const float& h) override;
	virtual const int& getTextureId() const override;

private:
	IRenderer * m_pRendererContext = nullptr;
};