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

	void EnablePhysics2D(const S2DPhysicalizeParams& params) override;

	bool AddCollisionListener(const SCollisionListenerParams& params) override;
	void RemoveCollisionListener(IEntity* pEntity) override; 

protected:
	ISystem * GetSystem() { return m_pSystem; }
	void ProcessCollisionCalculation();
	void ProcessGravity();

private:
	ISystem * m_pSystem = nullptr;
	std::map<IEntity*, SDL_Rect> m_collisionListeners{};
	std::vector<S2DPhysicalizeParams> m_physicalizedEntities{};
};