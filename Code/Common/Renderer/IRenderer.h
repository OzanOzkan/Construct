/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "../System/ISystem.h"
#include "IRenderObject.h"
#include "ITextureManager.h"
#include "ICamera.h"

struct RGBColor
{
	RGBColor() {}
	RGBColor(const float& R, const float& G, const float& B)
		: r(R)
		, g(G)
		, b(B)
	{}
	
	float r, g, b = 0;
};

enum class ERenderer : int
{
	NONE = 0,
	SDL2,
	OPENGL
};

class IRenderer : public IModule
{
public:
	virtual ~IRenderer() {}

	// IModule
	virtual void InitializeModule() = 0;
	virtual void onUpdate() = 0;
	// ~IModule

	virtual ITextureManager* GetTextureManager() = 0;
	virtual IRendererObject* CreateRenderObject(const SRenderObjectParams& params) = 0;
	virtual void RemoveRenderObject(IRendererObject* pRenderObject) = 0;
	virtual ICamera* GetCamera() = 0;
};