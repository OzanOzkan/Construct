#pragma once

#include <System/ISystem.h>

#include <string>

class CSDLFileOps
{
public:
	CSDLFileOps(ISystem* systemContext);

	std::string readFile(const std::string& file);

protected:
	ISystem* getSystem() { return m_pSystem; }

private:
	ISystem* m_pSystem;
};