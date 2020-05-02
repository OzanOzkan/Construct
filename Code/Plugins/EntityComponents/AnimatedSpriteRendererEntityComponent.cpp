#include "AnimatedSpriteRendererEntityComponent.h"

#include <System/EntitySystem/IEntity.h>
#include <Renderer/IRenderer.h>
#include <Renderer/IRenderObject.h>

/////////////////////////////////////////////////
AnimatedSpriteRendererEntityComponent::AnimatedSpriteRendererEntityComponent()
	: m_pAnimatedSprite(nullptr)
	, m_frameFiles({})
	, m_animationSpeed(1)
	, m_layerId(1)
	, m_loopListeners({})
{
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::Init()
{
}

/////////////////////////////////////////////////
unsigned int AnimatedSpriteRendererEntityComponent::getEventMask() const
{
	return EEntityEvent::ENTITY_EVENT_UPDATE | EEntityEvent::ENTITY_EVENT_DESTROY;
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::onEvent(const SEntityEvent & event)
{
	switch (event.GetEvent())
	{
	case EEntityEvent::ENTITY_EVENT_UPDATE:
	{
		onEntityUpdate();
	}
	break;
	case EEntityEvent::ENTITY_EVENT_DESTROY:
	{
		onEntityDestroy();
	}
	break;
	}
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::updateComponent()
{
	if (m_pAnimatedSprite) GetSystem()->GetRenderer()->RemoveRenderObject(m_pAnimatedSprite);

	SAnimatedSpriteParams animatedSpriteParams;
	animatedSpriteParams.position = getEntity()->getPosition() + getPosition();
	animatedSpriteParams.rotation = getRotation();
	animatedSpriteParams.animationSpeed = m_animationSpeed;
	animatedSpriteParams.layerId = m_layerId;

	for (auto frameFile : m_frameFiles)
	{
		animatedSpriteParams.addFrameFile(frameFile);
	}

	m_pAnimatedSprite = static_cast<IAnimatedSprite*>(GetSystem()->GetRenderer()->CreateRenderObject(animatedSpriteParams));
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::addFrameFile(const std::string & frameFile)
{
	m_frameFiles.emplace_back(frameFile);
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::resetFrames()
{
	m_frameFiles.clear();
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::setAnimationSpeed(const int & speed)
{
	if (m_pAnimatedSprite) m_pAnimatedSprite->setAnimationSpeed(speed);
	m_animationSpeed = speed;
}

/////////////////////////////////////////////////
int AnimatedSpriteRendererEntityComponent::getFrameCount()
{
	return m_pAnimatedSprite ? m_pAnimatedSprite->getFrameCount() : 0;
}

/////////////////////////////////////////////////
int AnimatedSpriteRendererEntityComponent::getCurrentFrame()
{
	return m_pAnimatedSprite ? m_pAnimatedSprite->getCurrentFrame() + 1 : 0;
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::setLayerId(const int & layerId)
{
	if (m_pAnimatedSprite) m_pAnimatedSprite->setLayerId(layerId);
	m_layerId = layerId;
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::onEntityUpdate()
{
	if (m_pAnimatedSprite)
	{
		m_pAnimatedSprite->setPosition(getEntity()->getPosition() + getPosition());
		m_pAnimatedSprite->setRotation(getRotation());

		for (auto loopListener : m_loopListeners)
		{
			loopListener(getCurrentFrame(), getFrameCount());
		}
	}
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::subscribeToAnimationLoop(TAnimatedSpriteRendererCallback fn)
{
	m_loopListeners.emplace_back(fn);
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::unsubscribeToAnimationLoop(TAnimatedSpriteRendererCallback fn)
{
	//m_loopListeners.erase(fn);
}

/////////////////////////////////////////////////
void AnimatedSpriteRendererEntityComponent::onEntityDestroy()
{
	if (m_pAnimatedSprite)
		GetSystem()->GetRenderer()->RemoveRenderObject(m_pAnimatedSprite);
}
