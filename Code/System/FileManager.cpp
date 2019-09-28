// Created by Ozan Ozkan - 28/09/2018

#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <algorithm>

/////////////////////////////////////////////////
CFileManager::CFileManager(SEnvironment * env)
	: m_pEnv(env)
{
}

/////////////////////////////////////////////////
std::string CFileManager::readFile(const std::string & file)
{
	std::ifstream ifs(file);
	std::string content;
	content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	ifs.close();

	return content;
}

/////////////////////////////////////////////////
void CFileManager::writeFile(const std::string & file, const std::string & data)
{
}