#pragma once

#include <string>

class ITexture
{
public:
	virtual ~ITexture() {}

	virtual bool LoadTexture(const std::string& filePath) = 0;
	virtual void DestroyTexture() = 0;
	virtual const std::string& GetFilePath() = 0;
};