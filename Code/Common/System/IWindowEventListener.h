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
	EWindowEventType event_type;

};

class IWindowEventListener
{
public:
	virtual void onWindowEvent(const SWindowEvent& event) = 0;
};