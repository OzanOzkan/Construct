#pragma once

#include <System/EntitySystem/IEntity.h>
#include <System/EntitySystem/IEntityBasicTypes.h>
#include <System/EntitySystem/IEntityComponent.h>

#include <queue>

class CEntity final : public IEntity
{
public:
	CEntity(ISystem* systemContext);
	
	// IEntity
	int getID() const { return m_entityID; }
	void setID(const int& entityId) { m_entityID = entityId; }
	void setName(const std::string& name) { m_entityName = name; }
	std::string getName() const { return m_entityName; }
	void setActive(const bool& isActive) { m_isActive = isActive; }
	bool isActive() const { return m_isActive; }
	int getComponentCount() const { return m_entityComponents.size(); };
	void setPosition(const Vector2& position) { m_entityPosition = position; }
	const Vector2& getPosition() { return m_entityPosition; }
	void setSize(const float& width, const float& height);
	void getSize(float& width, float& height) override;
	void setRotation(const float& rotation) { m_entityRotation = rotation; }
	float getRotation() { return m_entityRotation; }
	virtual void setTag(const std::string& tag) { m_tag = tag; }
	virtual const std::string& getTag() { return m_tag; }

	void sendEvent(const SEntityEvent& event) override;
	void setTimer(const float& seconds) override;
	// ~IEntity

	void MarkToDelete() { m_isMarkedToDelete = true; }
	const bool& IsMarkedToDelete() const { return m_isMarkedToDelete; }

	void removeEntityComponent(IEntityComponent* pEntityComponent) override;

protected:
	void addEntityComponentInternal(const std::string& componentName, std::unique_ptr<IEntityComponent> entityComponent) override;
	IEntityComponent* getEntityComponentInternal(const std::string& componentName) override;
	std::vector<IEntityComponent*> getEntityComponentsInternal(const std::string& componentName) override;

private:
	ISystem * GetSystem() { return m_pSystem; }
	void HandleEntityEventInternal(const SEntityEvent& event);
	void removeEntityComponentInternal();

private:
	int m_entityID;
	std::string m_entityName;
	bool m_isActive;
	std::string m_tag;
	std::multimap<std::string, std::unique_ptr<IEntityComponent>> m_entityComponents;
	std::queue<IEntityComponent*> m_componentsToDelete;
	Vector2 m_entityPosition;
	float m_width;
	float m_height;
	float m_entityRotation;
	bool m_isMarkedToDelete;
	bool m_timerSet;
	float m_timerSetTime;
	float m_timerSec;
};