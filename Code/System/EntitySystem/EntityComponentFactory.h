#pragma once

#include <System/EntitySystem/IEntitySystem.h>

class CEntityComponentFactory : public IEntityComponentFactory
{
public:
	IEntityComponent* Create(const std::string& name) override;
	void RegisterMaker(const std::string& name, IEntityComponentMaker* entityComponentMaker) override;

private:
	std::map<std::string, IEntityComponentMaker*> m_componentMakers;
};