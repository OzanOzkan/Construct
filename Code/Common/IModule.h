/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

template <typename T = int>
struct SCreateModuleParams {
	T implType;
};

class IModule
{
public:
	virtual ~IModule() {}

	virtual void InitializeModule() = 0;
	virtual void onUpdate() = 0;
};