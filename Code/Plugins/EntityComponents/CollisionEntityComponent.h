#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderObject.h>

class CollisionEntityComponent : public IEntityComponent
{
public:
	CollisionEntityComponent();

	// IEntityComponent
	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent& event) override;
	void updateComponent() override;
	// ~IEntityComponent

	void SetSize(const int& w, const int& h);
	void getSize(int& w, int& h);
	Vector2 getCenter();
	void setDebugDraw(const bool& isActive);

private:
	void onEntityDestroyEvent();
	void DebugDraw();

private:
	IRect * m_pDebugRect = nullptr;
	bool m_isDebugDraw = false;
	int m_width = -1;
	int m_height = -1;
};

REGISTER_ENTITY_COMPONENT(CollisionEntityComponent);