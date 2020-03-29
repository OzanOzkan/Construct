#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Math/Math.h>
#include <Renderer/IRenderObject.h>

typedef std::function<void(const Vector2& selectionPos)> TSelectionEventCallbackFn;

class OnSelectionListenerEntityComponent : public IEntityComponent
{
public:
	OnSelectionListenerEntityComponent();

	// IEntityComponent
	virtual void Init() override;
	virtual unsigned int getEventMask() const override;
	virtual void onEvent(const SEntityEvent & event) override;
	virtual void updateComponent() override;
	// ~IEntityComponent

	void subscribeOnSelection(TSelectionEventCallbackFn fn);
	void unsubscribeOnSelection(TSelectionEventCallbackFn fn);
	void setSize(const float& w, const float& h);
	void setDebugDraw(bool isActive);

private:
	void processInputEvent();
	bool checkSelection(const Vector2& positionToCheck);
	void updateBoundingBox();
	void debugDraw();

private:
	Math::Rectangle m_boundingBox;
	std::vector<TSelectionEventCallbackFn> m_callbacks;
	bool m_debugDraw;
	IRect* m_pBBDebugRect = nullptr;
	IRect* m_pInputDebugRect = nullptr;
};