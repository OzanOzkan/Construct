/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "../System/ISystem.h"
#include "IRenderObject.h"
#include "ITextureManager.h"

enum class ERenderer
{
	eRDR_NONE = 0,
	eRDR_SDL2,
	eRDR_OPENGL
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
};