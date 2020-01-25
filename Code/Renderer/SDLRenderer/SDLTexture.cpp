#include "SDLTexture.h"

#include <SDL_image.h>

///////////////////////////////////////////////////
CSDLTexture::CSDLTexture(SDL_Renderer* pSDLRenderer)
	: m_pSDLRenderer(pSDLRenderer)
{

}

///////////////////////////////////////////////////
bool CSDLTexture::LoadTexture(const std::string& filePath)
{
	m_textureFile = filePath;
	m_pSDLTexture = IMG_LoadTexture(m_pSDLRenderer, m_textureFile.c_str());
	
	return m_pSDLTexture ? true : false;
}

///////////////////////////////////////////////////
void CSDLTexture::DestroyTexture()
{
	if(m_pSDLTexture)
		SDL_DestroyTexture(m_pSDLTexture);
}

///////////////////////////////////////////////////
SDL_Texture* CSDLTexture::GetSDLTexturePtr()
{
	return m_pSDLTexture;
}

///////////////////////////////////////////////////
const std::string & CSDLTexture::GetFilePath()
{
	return m_textureFile;
}
