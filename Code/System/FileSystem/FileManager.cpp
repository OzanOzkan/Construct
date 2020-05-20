#include "FileManager.h"

#include <ILog.h>

#include <iostream>
#include <fstream>
#include <algorithm>

#ifdef _WIN32
#include <dirent/dirent.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <dirent.h>
#endif

#include "SDLFileOps.h"

/////////////////////////////////////////////////
CFileManager::CFileManager(ISystem* systemContext)
	: m_pSystem(systemContext)
{
}

/////////////////////////////////////////////////
std::string CFileManager::readFile(const std::string & file)
{
	//std::ifstream ifs;
	//ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	//std::string content;

	//try {
	//	ifs.open(file);
	//	content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	//	ifs.close();
	//}
	//catch (std::ifstream::failure e) {
	//	GetSystem()->GetLogger()->Log("FileManager::readFile: FILE_NOT_SUCCESFULLY_READ");
	//}

	CSDLFileOps sdlFileOps(m_pSystem);

	return sdlFileOps.readFile(file);
}

/////////////////////////////////////////////////
void CFileManager::writeFile(const std::string & file, const std::string & data)
{
}

/////////////////////////////////////////////////
std::string CFileManager::getAssetsDirectory()
{
	// Temporary implementation.

#ifdef _WIN32
	return "E:/Development/ProjectO01/Assets/";
#else
	return "";
#endif
}

/////////////////////////////////////////////////
std::string CFileManager::getWorkingDir()
{
#ifdef _WIN32
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
#else
	return "";
#endif
}

/////////////////////////////////////////////////
TDirectoryFileList CFileManager::getFilesInDirectory(const std::string& directory)
{
	TDirectoryFileList fileList;

	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(directory.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			fileList.push_back(ent->d_name);
		}
		closedir(dir);
	}

	return fileList;
}

/////////////////////////////////////////////////
TDirectoryFileList CFileManager::getFilesInDirectory(const std::string& directory, const std::string& extension)
{
	return TDirectoryFileList();
}
