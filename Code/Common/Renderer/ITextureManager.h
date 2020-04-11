#pragma once

#include "ITexture.h"
#include <string>

class ITextureManager
{
public:
	virtual ~ITextureManager() {}

	virtual int LoadTexture(const std::string& filePath) = 0;
	virtual void UnloadTexture(const int& textureId) = 0;
	virtual ITexture* GetTexture(const std::string& filePath) = 0;
	virtual ITexture* GetTexture(const int& textureId) = 0;
};