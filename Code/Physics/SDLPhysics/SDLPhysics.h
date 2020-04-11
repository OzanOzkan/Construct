#pragma once

#include <System/ISystem.h>
#include <Physics/IPhysics.h>

#include <SDL.h>

#include <map>

class CSDLPhysics : public IPhysics
{
public:
	CSDLPhysics(ISystem* systemContext);

	void InitializeModule() override;
	void onUpdate() override;

	bool AddCollisionListener(const SCollisionListenerParams& params) override;
	void RemoveCollisionListener(IEntity* pEntity) override; 

protected:
	ISystem * GetSystem() { return m_pSystem; }
	void ProcessCollisionCalculation();

private:
	ISystem * m_pSystem = nullptr;
	std::map<IEntity*, SDL_Rect> m_collisionListeners{};
};