/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#pragma once

enum class EWindowEventType
{
	eWE_NONE = 0,
	eWE_WINDOW_CLOSED,
	eWE_KEY_PRESSED,
	eWE_KEY_RELEASED,
	eWE_MOUSE_BUTTON_PRESSED,
	eWE_MOUSE_BUTTON_RELEASED,
	eWE_MOUSE_POSITION_CHANGED
};

struct SWindowEvent
{
	EWindowEventType event_type = EWindowEventType::eWE_NONE;
	int buttoncode = 0;
	int scancode = 0;
	double x = 0;
	double y = 0;
};

class IWindowEventListener
{
public:
	virtual void onWindowEvent(const SWindowEvent& event) = 0;
};