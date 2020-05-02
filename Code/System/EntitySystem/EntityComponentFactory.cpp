#include "EntityComponentFactory.h"

/////////////////////////////////////////////////
IEntityComponentFactory& IEntitySystem::getEntityComponentFactory()
{
    static CEntityComponentFactory instance;
    return instance;
}

/////////////////////////////////////////////////
void CEntityComponentFactory::RegisterMaker(const std::string& name, IEntityComponentMaker* entityComponentMaker)
{
    if (m_componentMakers.find(name) == m_componentMakers.end()) {
        m_componentMakers[name] = entityComponentMaker;
    }    
}

/////////////////////////////////////////////////
IEntityComponent* CEntityComponentFactory::Create(const std::string& name)
{
    auto i = m_componentMakers.find(name);
    if (i != m_componentMakers.end()) {
        return i->second->Create();
    }

    return nullptr;
}