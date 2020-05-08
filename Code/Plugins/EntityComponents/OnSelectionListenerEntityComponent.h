#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Math/Math.h>
#include <Renderer/IRenderObject.h>

#include <functional>

typedef std::function<void(const bool& isSelected, const Vector2& selectionPos)> TSelectionEventCallbackFn;

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

	void getClassDesc(std::map<std::string, void*>& desc) {
		desc.emplace("width", &m_boundingBox.w);
		desc.emplace("height", &m_boundingBox.h);
		desc.emplace("debugDraw", &m_debugDraw);
	}

	void subscribeOnSelection(TSelectionEventCallbackFn fn);
	void unsubscribeOnSelection(TSelectionEventCallbackFn fn);
	void setSize(const float& w, const float& h);
	void setDebugDraw(bool isActive);

private:
	void processSelectionEvent();
	bool checkSelection(const Vector2& positionToCheck);
	void notifyListeners(const bool& isSelected, const Vector2& selectionPos);
	void updateBoundingBoxPosition();
	void debugDraw();

private:
	Math::Rectangle m_boundingBox;
	std::vector<TSelectionEventCallbackFn> m_callbacks;
	Vector2 m_lastSelectedPosition;
	bool m_isSelectedPreviousFrame;
	bool m_debugDraw;
	IRect* m_pBBDebugRect;
	IRect* m_pInputDebugRect;
};

REGISTER_ENTITY_COMPONENT(OnSelectionListenerEntityComponent);