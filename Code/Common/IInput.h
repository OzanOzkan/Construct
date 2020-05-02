/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "Core.h"
#include "System/ISystem.h"
#include "IModule.h"
#include "Math/Math.h"

#include <vector>

enum class EInput : int
{
	NONE = 0,
	SDL2
};

enum class EKey
{
	eKID_UNKNOWN = 0,

	eKID_A = 4,
	eKID_B = 5,
	eKID_C = 6,
	eKID_D = 7,
	eKID_E = 8,
	eKID_F = 9,
	eKID_G = 10,
	eKID_H = 11,
	eKID_I = 12,
	eKID_J = 13,
	eKID_K = 14,
	eKID_L = 15,
	eKID_M = 16,
	eKID_N = 17,
	eKID_O = 18,
	eKID_P = 19,
	eKID_Q = 20,
	eKID_R = 21,
	eKID_S = 22,
	eKID_T = 23,
	eKID_U = 24,
	eKID_V = 25,
	eKID_W = 26,
	eKID_X = 27,
	eKID_Y = 28,
	eKID_Z = 29,

	eKID_1 = 30,
	eKID_2 = 31,
	eKID_3 = 32,
	eKID_4 = 33,
	eKID_5 = 34,
	eKID_6 = 35,
	eKID_7 = 36,
	eKID_8 = 37,
	eKID_9 = 38,
	eKID_0 = 39,

	eKID_RETURN = 40,
	eKID_ESCAPE = 41,
	eKID_BACKSPACE = 42,
	eKID_TAB = 43,
	eKID_SPACE = 44,

	eKID_MOUSE_LEFT = 1000,
	eKID_MOUSE_MIDDLE = 1001,
	eKID_MOUSE_RIGHT = 1002
};

struct STouchEvent
{
	int fingerId;
	Vector2 position;
	float pressure;
};

using STouchEventList = std::vector<STouchEvent>;

class IInput : public IModule
{
public:
	// IModule
	virtual void			InitializeModule() = 0;
	virtual void			onUpdate() = 0;
	// ~IModule

	virtual bool			IsKeyPressed(const EKey& key) = 0;
	virtual Vector2			GetMousePosition() = 0;
	virtual STouchEventList GetTouchEvents() = 0;
};