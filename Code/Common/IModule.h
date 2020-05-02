#pragma once

template <typename T = int>
struct SCreateModuleParams {
	T implType;
};

class IModule
{
public:
	virtual void InitializeModule() = 0;
	virtual void onUpdate() = 0;
};