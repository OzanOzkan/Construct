#include "Renderer.h"

#include <ISystem.h>

#include <ILog.h>

extern "C"
{
	EXTERN_LIBRARY_EXPORT IRenderer* CreateModuleInterface(SEnvironment *env)
	{
		std::unique_ptr<CRenderer> pRenderer = std::make_unique<CRenderer>(env);

		return pRenderer.release();
	}
}

/////////////////////////////////////////////////
CRenderer::CRenderer(SEnvironment* env)
	: m_pEnv(env)
{
	InitializeModule();
}

/////////////////////////////////////////////////
CRenderer::~CRenderer()
{

}

/////////////////////////////////////////////////
void CRenderer::InitializeModule()
{
	initWindow();
}

/////////////////////////////////////////////////
void CRenderer::initWindow()
{
	m_window = std::make_unique<CWindow>();
	m_window->initWindow();
	m_window->addEventListener(this);
}

/////////////////////////////////////////////////
void CRenderer::Update()
{
	m_window->onUpdate();
}

/////////////////////////////////////////////////
void CRenderer::onWindowEvent(const int & key, const int & action)
{
	// Wrapper for keys.
	m_pEnv->pLog->Log("CRenderer::onWindowEvent: GLFW_KEY_E : GLFW_KEY_PRESS");
}