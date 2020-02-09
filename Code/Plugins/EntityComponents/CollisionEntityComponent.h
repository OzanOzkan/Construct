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

private:
	void onEntityDestroyEvent();
	void DebugDraw();

private:
	IRect * m_pDebugRect = nullptr;
	int m_width = -1;
	int m_height = -1;
};