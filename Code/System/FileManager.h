/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/IFileManager.h>
#include <System/ISystem.h>

class CFileManager : public IFileManager
{
public:
	CFileManager(ISystem* systemContext);

	std::string readFile(const std::string& file) override;
	void writeFile(const std::string& file, const std::string& data) override;
	std::string getAssetsDirectory() override;

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem* m_pSystem;
};