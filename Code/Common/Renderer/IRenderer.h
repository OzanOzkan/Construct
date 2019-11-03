/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "../Core.h"
#include "../IModule.h"
#include "../System/ISystem.h"
#include "IRenderObject.h"

struct SSpriteRenderParams
{
	int texture_id = -1;
	float posX = -1;
	float posY = -1;
	float w = -1;
	float h = -1;
};

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

	// Texture
	virtual int LoadTexture(const std::string& filePath) = 0;
	virtual void UnloadTexture(const int& textureId) = 0;
	// ~Texture

	// Sprite
	virtual ISprite* CreateSprite(const SSpriteCreateParams& params) = 0;
	virtual void RemoveSprite(ISprite* pSprite) = 0;
	//virtual void RenderSprite(const SSpriteRenderParams& params) = 0;
	// ~Sprite
};