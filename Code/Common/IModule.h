#pragma once

enum class EModule
{
	eM_SYSTEM = 0,
	eM_RENDERER,
	eM_INPUT
};

class IModule
{
public:
	virtual ~IModule() {}

	virtual void InitializeModule() = 0;
	virtual void Update() = 0;
};