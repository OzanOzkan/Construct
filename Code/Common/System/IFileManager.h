#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> TDirectoryFileList;

class IFileManager
{
public:
	virtual ~IFileManager() = default;

	virtual std::string			readFile(const std::string& file) = 0;
	virtual void				writeFile(const std::string& file, const std::string& data) = 0;
	virtual std::string			getAssetsDirectory() = 0;
	virtual std::string			getWorkingDir() = 0;
	virtual TDirectoryFileList	getFilesInDirectory(const std::string& directory) = 0;
	virtual TDirectoryFileList	getFilesInDirectory(const std::string& directory, const std::string& extension) = 0;
};