#pragma once

#include <ISystem.h>

class CSystem : public ISystem {

public:
	CSystem();
	virtual ~CSystem();

	// ISystemInterface
	virtual void InitializeModule() override;
	// ~ISystemInterface

	virtual void Update() override;
	//virtual SGlobalEnvironment* getGlobalEnvironment() override { return &m_env; }

	void CreateModuleInstance(const EModule& moduleName);

private:
	SGlobalEnvironment m_env;
	bool m_isQuit = false;
};