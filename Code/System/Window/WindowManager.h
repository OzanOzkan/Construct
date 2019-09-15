#pragma once

#include <memory>
#include <set>
#include <functional>

#include <System/IWindowManager.h>

#include "GLFWWindow.h"

class CWindowManager : public IWindowManager
{
public:
	CWindowManager() {};
	virtual ~CWindowManager() {};

	// IWindowManager
	virtual void initWindow() override;
	virtual void setWindowSize(const int& height, const int& width) override;
	virtual void onUpdate() override;

	virtual void registerWindowEvents(IWindowEventListener* listener) override;
	virtual void unregisterWindowEvents(IWindowEventListener* listener) override;
	virtual void onWindowEvent(const SWindowEvent& event) override;
	// ~IWindowManager

private:
	void notifyListeners(const SWindowEvent& event);

private:
	int m_height = 800;
	int m_width = 600;

	std::unique_ptr<CGLFWWindow> m_activeWindow = nullptr;
	std::set<IWindowEventListener*> m_eventListeners{};
};