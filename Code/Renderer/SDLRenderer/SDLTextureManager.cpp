#include "SDLTextureManager.h"
#include <SDL_image.h>

///////////////////////////////////////////////////
CSDLTextureManager::CSDLTextureManager(ISystem * systemContext, SDL_Renderer* pSDLRenderer)
	: m_pSystem(systemContext)
	, m_pSDLRenderer(pSDLRenderer)
	, m_loadedTextures()
	, m_textureFileIdMap()
{
}

///////////////////////////////////////////////////
CSDLTextureManager::~CSDLTextureManager()
{
	DestroyLoadedTextures();
}

///////////////////////////////////////////////////
int CSDLTextureManager::LoadTexture(const std::string & filePath)
{
	int textureId = 0;

	// Check if the same texture already loaded before.
	int resolveId = ResolveTextureId(filePath);
	if (resolveId > -1)
	{
		// Be more safe and check loaded texture map as well.
		if (GetTexture(resolveId))
			textureId = resolveId;
	}
	else
	{
		// Generate a new texture id. Todo: Use GUID?
		if (m_loadedTextures.size() > 0)
		{
			textureId = m_loadedTextures.rbegin()->first + 1;
		}

		std::unique_ptr<CSDLTexture> pTexture = std::make_unique<CSDLTexture>(m_pSDLRenderer);
		pTexture->LoadTexture(filePath);

		m_loadedTextures.emplace(std::make_pair(textureId, std::move(pTexture)));
		m_textureFileIdMap.emplace(filePath, textureId);
	}

	return textureId;
}

///////////////////////////////////////////////////
void CSDLTextureManager::UnloadTexture(const int & textureId)
{
	if (m_loadedTextures.size() > 1)
	{
		if (CSDLTexture* pTexture = m_loadedTextures.at(textureId).get())
		{
			pTexture->DestroyTexture();
			m_loadedTextures.erase(textureId);

			// Erase it from file - id map as well.
			for (auto mapElem : m_textureFileIdMap)
			{
				if (mapElem.second == textureId)
				{
					m_textureFileIdMap.erase(mapElem.first);
					break;
				}
			}
		}
	}
}

///////////////////////////////////////////////////
CSDLTexture * CSDLTextureManager::GetTexture(const std::string & filePath)
{
	CSDLTexture* pRetTexture = nullptr;

	auto textureItr = m_loadedTextures.find(ResolveTextureId(filePath));
	if (textureItr != m_loadedTextures.end())
		pRetTexture = textureItr->second.get();

	return pRetTexture;
}

///////////////////////////////////////////////////
CSDLTexture * CSDLTextureManager::GetTexture(const int & textureId)
{
	auto textureItr = m_loadedTextures.find(textureId);
	if (textureItr != m_loadedTextures.end())
		return textureItr->second.get();
	else
		return nullptr;
}

///////////////////////////////////////////////////
int CSDLTextureManager::ResolveTextureId(const std::string & filePath)
{
	int retId = -1;

	auto fileIdItr = m_textureFileIdMap.find(filePath);
	if (fileIdItr != m_textureFileIdMap.end())
		retId = fileIdItr->second;

	return retId;
}

///////////////////////////////////////////////////
void CSDLTextureManager::DestroyLoadedTextures()
{
	for (auto& textureItr : m_loadedTextures)
	{
		textureItr.second->DestroyTexture();
	}

	m_loadedTextures.clear();
	m_textureFileIdMap.clear();
}
