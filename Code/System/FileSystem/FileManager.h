#pragma once

#include <System/IFileManager.h>
#include <System/ISystem.h>

class CFileManager : public IFileManager
{
public:
	CFileManager(ISystem* systemContext);

	std::string getAssetsDirectory() override;
	std::string getWorkingDir() override;
	TDirectoryFileList getFilesInDirectory(const std::string& directory) override;
	TDirectoryFileList getFilesInDirectory(const std::string& directory, const std::string& extension) override;
	std::string readFile(const std::string& file) override;
	void writeFile(const std::string& file, const std::string& data) override;

private:
	ISystem * GetSystem() { return m_pSystem; }

private:
	ISystem* m_pSystem;
};