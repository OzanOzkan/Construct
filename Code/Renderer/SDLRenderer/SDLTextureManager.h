#pragma once

#include <System/ISystem.h>
#include <ILog.h>

#include <SDL.h>

#include <map>

class CSDLTextureManager
{
public:
	CSDLTextureManager(ISystem* systemContext, SDL_Renderer* pSDLRenderer);
	virtual ~CSDLTextureManager();

	int LoadTexture(const std::string& filePath);
	void UnloadTexture(const int& textureId);
	SDL_Texture* GetTexture(const std::string& filePath);
	SDL_Texture* GetTexture(const int& textureId);
	
	int ResolveTextureId(const std::string& filePath);

private:
	ISystem * GetSystem() { return m_pSystem; }
	void DestroyLoadedTextures();

private:
	ISystem * m_pSystem = nullptr;
	SDL_Renderer* m_pSDLRenderer = nullptr;
	
	std::map<int, SDL_Texture*> m_loadedTextures{};
	std::map<std::string, int> m_textureFileIdMap{};
};