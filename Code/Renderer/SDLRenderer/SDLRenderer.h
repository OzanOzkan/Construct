#pragma once

#include <System/ISystem.h>
#include <Renderer/IRenderer.h>
#include <Renderer/IRenderObject.h>

#include <SDL.h>

#include <map>

#include <Math/Math.h>

#include "SDLTextureManager.h"

class CText;

class CSDLRenderer : public IRenderer
{
public:
	CSDLRenderer(ISystem* systemContext);

	// Inherited via IRenderer
	void InitializeModule() override;
	void onUpdate() override;
	// ~IRenderer

	// RenderObject
	IRendererObject* CreateRenderObject(const SRenderObjectParams& params) override;
	void RemoveRenderObject(IRendererObject* pRenderObject) override;
	// RenderObject

	// Texture (Todo: Will be moved to upper Renderer class)
	int LoadTexture(const std::string& filePath) override { return -1; }
	void UnloadTexture(const int& textureId) override {}
	// ~Texture

	CSDLTextureManager* GetTextureManager() { return m_pTextureManager.get(); }

	void doRender();

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem;
	std::unique_ptr<CSDLTextureManager> m_pTextureManager;
	SDL_Window* m_pSDLWindow;
	SDL_Renderer* m_pSDLRenderer;

	std::multimap<int, int> m_renderLayerMap{};
	std::map<int, std::unique_ptr<IRendererObject>> m_renderObjectList{};
};