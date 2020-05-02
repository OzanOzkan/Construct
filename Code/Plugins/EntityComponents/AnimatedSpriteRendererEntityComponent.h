#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderObject.h>

#include <functional>

typedef std::function<void(const int& currentFrame, const int& frameCount)> TAnimatedSpriteRendererCallback;

class AnimatedSpriteRendererEntityComponent : public IEntityComponent
{
public:
	AnimatedSpriteRendererEntityComponent();

	void Init() override;
	unsigned int getEventMask() const override;
	void onEvent(const SEntityEvent & event) override;
	void updateComponent() override;

	void addFrameFile(const std::string& frameFile);
	void resetFrames();
	void setAnimationSpeed(const int& speed);
	int getFrameCount();
	int getCurrentFrame();
	void setLayerId(const int& layerId);
	void subscribeToAnimationLoop(TAnimatedSpriteRendererCallback fn);
	void unsubscribeToAnimationLoop(TAnimatedSpriteRendererCallback fn);

private:
	void onEntityUpdate();
	void onEntityDestroy();

private:
	IAnimatedSprite* m_pAnimatedSprite;
	std::vector<std::string> m_frameFiles;
	int m_animationSpeed;
	int m_layerId;
	std::vector<TAnimatedSpriteRendererCallback> m_loopListeners;
};

REGISTER_ENTITY_COMPONENT(AnimatedSpriteRendererEntityComponent);