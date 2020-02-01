#pragma once

#include <Renderer/ITexture.h>
#include <SDL.h>

class CSDLTexture final : public ITexture
{
public:
	CSDLTexture(SDL_Renderer* pSDLRenderer);

	bool LoadTexture(const std::string& filePath, const int& id) override;
	const std::string& GetFilePath() override;
	void DestroyTexture() override;
	int GetId() override;

	SDL_Texture* GetSDLTexturePtr();

private:
	std::string m_textureFile;
	int m_textureId = -1;
	SDL_Renderer* m_pSDLRenderer = nullptr;
	SDL_Texture* m_pSDLTexture = nullptr;
};