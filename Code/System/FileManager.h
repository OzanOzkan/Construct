/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include <System/IFileManager.h>
#include <System/ISystem.h>

class CFileManager : public IFileManager
{
public:
	CFileManager(SEnvironment* env);
	virtual ~CFileManager() {}

	virtual std::string readFile(const std::string& file) override;
	virtual void writeFile(const std::string& file, const std::string& data) override;

private:
	SEnvironment * m_pEnv;
};