#pragma once

#include "../../Core.h"
#include "../../Math/Math.h"

#include <string>
#include <map>
#include <memory>

class IEntity;
class IEntityComponent;
class IEntityComponentFactory;

struct SEntitySpawnParams
{
	std::string entityName = "";
	Vector2 position{ 0, 0 };
	float width = 0.f;
	float height = 0.f;
};

class IEntitySystem
{
public:
	virtual IEntity* spawnEntity(const SEntitySpawnParams& spawnParams) = 0;
	virtual void destroyEntity(const int& entityId) = 0;
	virtual int getEntityCount() const = 0;
	virtual void addEntityEventListener(IEntity* pEntity) = 0;
	virtual void removeEntityEventListener(IEntity* pEntity) = 0;

    // Singleton Abstract Factory for EntityComponents
    static IEntityComponentFactory& getEntityComponentFactory();

	// Will be removed.
	virtual void onUpdate() = 0;
};

class IEntityComponentFactory
{
public:
    class IEntityComponentMaker
    {
    public:
        virtual IEntityComponent* Create() = 0;
        virtual ~IEntityComponentMaker() {}
    };

    template <typename T>
    class EntityComponentMaker : public IEntityComponentMaker
    {
    public:
        EntityComponentMaker(const std::string& name) {
            IEntitySystem::getEntityComponentFactory().RegisterMaker(name, this);
        }

        IEntityComponent* Create() override {
            return new T;
        }
    };

    virtual IEntityComponent* Create(const std::string& name) = 0;
    virtual void RegisterMaker(const std::string& name, IEntityComponentMaker* entityComponentMaker) = 0;
};

#define REGISTER_ENTITY_COMPONENT(T) static IEntityComponentFactory::EntityComponentMaker<T> componentMaker##T(#T);