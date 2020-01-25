#pragma once

#include <Renderer/ITexture.h>
#include <SDL.h>

class CSDLTexture final : public ITexture
{
public:
	CSDLTexture(SDL_Renderer* pSDLRenderer);

	bool LoadTexture(const std::string& filePath) override;
	const std::string& GetFilePath() override;
	void DestroyTexture() override;

	SDL_Texture* GetSDLTexturePtr();

private:
	std::string m_textureFile;
	SDL_Renderer* m_pSDLRenderer = nullptr;
	SDL_Texture* m_pSDLTexture = nullptr;
};