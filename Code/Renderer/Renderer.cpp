#include "Renderer.h"

#include <System/ISystem.h>

#include <ILog.h>

extern "C"
{
	API_EXPORT IRenderer* CreateModuleInterface(SEnvironment *env)
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

}

/////////////////////////////////////////////////
void CRenderer::Update()
{

}
