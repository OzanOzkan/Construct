#pragma once

#include <System/ISystem.h>
#include <Renderer/IRenderer.h>
#include <Renderer/IRenderObject.h>

#include <SDL.h>

#include <queue>
#include <map>
#include <set>

#include <Math/Math.h>

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

	// Texture
	int LoadTexture(const std::string& filePath) override;
	void UnloadTexture(const int& textureId) override;
	// ~Texture

	void doRender();

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem * m_pSystem;
	SDL_Window* m_pSDLWindow;
	SDL_Renderer* m_pSDLRenderer;

	std::map<int, SDL_Texture*> m_loadedTextures;
	std::map<int, std::unique_ptr<IRendererObject>> m_renderObjectList; // Todo: ordered map for layers
};