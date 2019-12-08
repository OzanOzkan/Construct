/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "FileManager.h"

#include <ILog.h>

#include <iostream>
#include <fstream>
#include <algorithm>

/////////////////////////////////////////////////
CFileManager::CFileManager(ISystem* systemContext)
	: m_pSystem(systemContext)
{
}

/////////////////////////////////////////////////
std::string CFileManager::readFile(const std::string & file)
{
	std::ifstream ifs;
	ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string content;

	try 
	{
		ifs.open(file);
		content.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		ifs.close();
	}
	catch (std::ifstream::failure e)
	{
		GetSystem()->GetLogger()->Log("FileManager::readFile: FILE_NOT_SUCCESFULLY_READ");
	}
	
	return content;
}

/////////////////////////////////////////////////
void CFileManager::writeFile(const std::string & file, const std::string & data)
{
}