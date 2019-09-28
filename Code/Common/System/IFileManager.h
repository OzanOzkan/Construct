#pragma once

#include <string>

class IFileManager
{
public:
	virtual ~IFileManager() {}

	virtual std::string readFile(const std::string& file) = 0;
	virtual void writeFile(const std::string& file, const std::string& data) = 0;
};