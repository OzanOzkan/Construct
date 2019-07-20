#include "Renderer.h"

#include <Platform.h>

#include "ILog.h"

extern "C"
{
	EXTERN_LIBRARY_EXPORT IRenderer* CreateModuleInterface(SGlobalEnvironment &env)
	{
		std::unique_ptr<CRenderer> pRenderer = std::make_unique<CRenderer>(env);

		return pRenderer.release();
	}
}

CRenderer::CRenderer(SGlobalEnvironment &env)
{
	env.pRenderer = this;
	gEnv = &env; // ????????
	InitializeModule();
}

CRenderer::~CRenderer()
{

}

void CRenderer::InitializeModule()
{
	initWindow();
}

void CRenderer::initWindow()
{
	m_window = std::make_unique<CWindow>();
	m_window->initWindow();
}

void CRenderer::Update()
{
	m_window->onUpdate();

	gEnv->pLog->Log("CRenderer::Update()");
}