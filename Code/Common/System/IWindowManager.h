/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

#include "IWindowEventListener.h"

#include <functional>

typedef struct {
	float width = -1;
	float height = -1;
} SWindowSize;

class IWindowManager
{
public:
	virtual const int& GetWindowId() = 0;
	virtual const SWindowSize& GetWindowSize() = 0;
};