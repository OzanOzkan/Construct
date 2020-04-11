#pragma once

#include "../Math/Math.h"

class ICamera
{
public:
	virtual void SetPosition(const Vector2& position) = 0;
	virtual const Vector2& GetPosition() = 0;
	virtual void SetSize(const float& width, const float& height) = 0;
	virtual void GetSize(float& width, float& height) = 0;
};