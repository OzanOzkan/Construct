#pragma once

#include <System/ISystem.h>
#include <Renderer/IRenderer.h>
#include <Renderer/IRenderObject.h>
#include <Math/Math.h>

#include <SDL.h>

#include <map>

#include "SDLTextureManager.h"

class CText;

class CSDLRenderer : public IRenderer
{
public:
	CSDLRenderer(ISystem* systemContext);

	// IRenderer
	void InitializeModule() override;
	void onUpdate() override;

	CSDLTextureManager* GetTextureManager() override { return m_pTextureManager.get(); }
	IRendererObject* CreateRenderObject(const SRenderObjectParams& params) override;
	void RemoveRenderObject(IRendererObject* pRenderObject) override;
	// ~IRenderer

	void doRender();
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem;
	std::unique_ptr<CSDLTextureManager> m_pTextureManager;
	SDL_Window* m_pSDLWindow;
	SDL_Renderer* m_pSDLRenderer;

	std::multimap<int, int> m_renderLayerMap{};
	std::map<int, std::unique_ptr<IRendererObject>> m_renderObjectList{};
};