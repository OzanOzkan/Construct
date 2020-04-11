#pragma once

#include <System/EntitySystem/IEntityComponent.h>
#include <Renderer/IRenderObject.h>

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

private:
	void onEntityUpdate();
	void onEntityDestroy();

private:
	IAnimatedSprite* m_pAnimatedSprite;
	std::vector<std::string> m_frameFiles;
	int m_animationSpeed;
	int m_layerId;
};