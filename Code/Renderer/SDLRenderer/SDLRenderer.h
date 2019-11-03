#pragma once

#include <System/ISystem.h>
#include <Renderer/IRenderer.h>
#include <Renderer/IRenderObject.h>

#include <SDL.h>
#include <SDL_image.h>

#include <queue>
#include <map>
#include <set>

class CSDLRenderer : public IRenderer
{
public:
	CSDLRenderer(SEnvironment* env);
	virtual ~CSDLRenderer() {}

	// Inherited via IRenderer
	virtual void InitializeModule() override;
	virtual void onUpdate() override;

	virtual int LoadTexture(const std::string& filePath) override;
	virtual void UnloadTexture(const int& textureId) override;

	virtual ISprite* CreateSprite(const SSpriteCreateParams& params) override;
	virtual void RemoveSprite(ISprite* pSprite) override;
	//virtual void RenderSprite(const SSpriteRenderParams& params) override;

	void doRender();

private:
	SEnvironment * m_pEnv = nullptr;
	SDL_Window* m_pSDLWindow = nullptr;
	SDL_Renderer* m_pSDLRenderer = nullptr;

	std::map<int, SDL_Texture*> m_loadedTextures{};
	std::map<int, std::unique_ptr<IRendererObject>> m_renderObjectList{};
};