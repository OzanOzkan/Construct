#pragma once

#include <memory>
#include <set>
#include <functional>

#include <System/ISystem.h>
#include "Window.h"

enum class EWindowType
{
	eWT_NONE = 0,
	eWT_SDL2
};

class CWindowManager : public IWindowManager
{
public:
	CWindowManager(ISystem* systemContext);

	// IWindowManager
	const int& GetWindowId() override;
	const SWindowSize& GetWindowSize() override;
	void setWindowSize(const int& width, const int& height) override;
	// ~IWindowManager

	void initWindow(const EWindowType& windowType, void* renderTarget);
	void onPreUpdate() {}
	void onUpdate();
	void onPostUpdate() {}

	void registerWindowEvents(IWindowEventListener* listener);
	void unregisterWindowEvents(IWindowEventListener* listener);
	void onWindowEvent(const SWindowEvent& event);

	int getTicks() { return m_activeWindow->getTicks(); }

private:
	ISystem * GetSystem() { return m_pSystem; }
	void notifyListeners(const SWindowEvent& event);

private:
	ISystem * m_pSystem;
	int m_height;
	int m_width;
	std::unique_ptr<CWindow> m_activeWindow;
	std::set<IWindowEventListener*> m_eventListeners;
};