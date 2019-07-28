#pragma once

#include <memory>
#include <set>
#include <functional>

#include <System/IWindowEventListener.h>

#include "GLFWWindow.h"

class CWindowManager
{
public:
	CWindowManager() {};
	virtual ~CWindowManager() {};

	void setSize(const int& height, const int& width);
	void initWindow();

	void addEventListener(IWindowEventListener* listener);
	void removeEventListener(IWindowEventListener* listener);

	void onUpdate();

	void onWindowEvent(const SWindowEvent& event);

private:
	void notifyListeners(const SWindowEvent& event);

private:
	int m_height = 800;
	int m_width = 600;

	std::unique_ptr<CGLFWWindow> m_activeWindow = nullptr;
	std::set<IWindowEventListener*> m_eventListeners{};
};