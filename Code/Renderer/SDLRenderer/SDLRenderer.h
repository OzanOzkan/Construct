#pragma once

#include <System/ISystem.h>
#include <Renderer/IRenderer.h>
#include <Renderer/IRenderObject.h>
#include <Math/Math.h>

#include <SDL.h>

#include <map>

#include "SDLTextureManager.h"
#include "SDLCamera.h"

class CText;

class CSDLRenderer : public IRenderer
{
public:
	CSDLRenderer(ISystem* systemContext);

	// IRenderer
	void InitializeModule() override;
	void onUpdate() override;
	void setResolution(const int& width, const int& height) override;
	void getResolution(int& width, int& height) override;

	CSDLTextureManager* GetTextureManager() override { return m_pTextureManager.get(); }
	IRendererObject* CreateRenderObject(const SRenderObjectParams& params) override;
	void RemoveRenderObject(IRendererObject* pRenderObject) override;
	ICamera* GetCamera() override { return m_pCamera.get(); }
	// ~IRenderer

	void doRender();
	ISystem * GetSystem() { return m_pSystem; }

private:
	int m_defaultRenderWidth;
	int m_defaultRenderHeight;
	ISystem * m_pSystem;
	std::unique_ptr<CSDLCamera> m_pCamera;
	std::unique_ptr<CSDLTextureManager> m_pTextureManager;
	SDL_Window* m_pSDLWindow;
	SDL_Renderer* m_pSDLRenderer;

	std::multimap<int, int> m_renderLayerMap{};
	std::map<int, std::unique_ptr<IRendererObject>> m_renderObjectList{};
};