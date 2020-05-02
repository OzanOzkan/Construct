#pragma once

#include <string>

class ITexture
{
public:
	virtual bool LoadTexture(const std::string& filePath, const int& id) = 0;
	virtual void DestroyTexture() = 0;
	virtual const std::string& GetFilePath() = 0;
	virtual int GetId() = 0;
};