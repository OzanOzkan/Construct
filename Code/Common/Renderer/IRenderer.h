#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "../System/ISystem.h"
#include "IRenderObject.h"
#include "ITextureManager.h"
#include "ICamera.h"

enum class ERenderer : int
{
	NONE = 0,
	SDL2,
	OPENGL
};

class IRenderer : public IModule
{
public:
	// IModule
	virtual void InitializeModule() = 0;
	virtual void onUpdate() = 0;
	// ~IModule

	virtual ITextureManager*	GetTextureManager() = 0;
	virtual IRendererObject*	CreateRenderObject(const SRenderObjectParams& params) = 0;
	virtual void				RemoveRenderObject(IRendererObject* pRenderObject) = 0;
	virtual ICamera*			GetCamera() = 0;
	virtual void				setResolution(const int& width, const int& height) = 0;
	virtual void				getResolution(int& width, int& height) = 0;
};