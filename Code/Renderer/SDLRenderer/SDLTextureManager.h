#pragma once

#include <System/ISystem.h>
#include <Renderer/ITextureManager.h>
#include <ILog.h>

#include "SDLTexture.h"

#include <SDL.h>

#include <map>

class CSDLTextureManager final : public ITextureManager
{
public:
	CSDLTextureManager(ISystem* systemContext, SDL_Renderer* pSDLRenderer);
	virtual ~CSDLTextureManager();

	// ITextureManager
	int LoadTexture(const std::string& filePath) override;
	void UnloadTexture(const int& textureId) override;
	CSDLTexture* GetTexture(const std::string& filePath) override;
	CSDLTexture* GetTexture(const int& textureId) override;
	int getLoadedTextureCount() override;
	// ~ITextureManager

	int ResolveTextureId(const std::string& filePath);

private:
	ISystem * GetSystem() { return m_pSystem; }
	void DestroyLoadedTextures();

private:
	ISystem * m_pSystem = nullptr;
	SDL_Renderer* m_pSDLRenderer = nullptr;
	
	std::map<int, std::unique_ptr<CSDLTexture>> m_loadedTextures{};
	std::map<std::string, int> m_textureFileIdMap{};
};