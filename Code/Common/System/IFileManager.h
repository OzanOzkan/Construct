/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <string>
#include <vector>

class IFileManager
{
public:
	virtual ~IFileManager() = default;

	virtual std::string readFile(const std::string& file) = 0;
	virtual void writeFile(const std::string& file, const std::string& data) = 0;
	virtual std::string getAssetsDirectory() = 0;
};