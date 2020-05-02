#pragma once

#include "IWindowEventListener.h"

typedef struct {
	float width = -1;
	float height = -1;
} SWindowSize;

class IWindowManager
{
public:
	virtual const int&			GetWindowId() = 0;
	virtual const SWindowSize&	GetWindowSize() = 0;
	virtual void				setWindowSize(const int& width, const int& height) = 0;
};