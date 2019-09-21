#include "Renderer.h"

#include <System/ISystem.h>
#include <ILog.h>

#include <glad/glad.h>

#include <GL/GL.h>

#include <string>

/////////////////////////////////////////////////
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
	if (!gladLoadGLLoader((GLADloadproc)m_pEnv->pSystem->getWindowProcAddress()))
		m_pEnv->pLog->Log("CGLFWWindow::openWindow: Failed to load GLAD.");

	m_pEnv->pSystem->registerWindowEvents(this);

	glViewport(0, 0, 800, 600);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glOrtho(0.0, 800.0, 0.0, 600.0, 0.0, 1.0);

#pragma region EXPERIMENTAL
	std::string glversiontxt("CRenderer::InitializeModule(): OpenGL Version: ");
	std::string glversion ((char*)glGetString(GL_VERSION));
	glversiontxt += glversion;
	m_pEnv->pLog->Log(glversiontxt.c_str());

#pragma endregion EXPERIMENTAL
}

/////////////////////////////////////////////////
void CRenderer::onUpdate()
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region EXPERIMENTAL
	float size = 10.0;
	int x = tempMouseX;
	int y = 600 - tempMouseY;
	glColor3f(tempColor, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);

#pragma region EXPERIMENTAL
	glEnd();
	glFlush();
}

/////////////////////////////////////////////////
void CRenderer::onWindowEvent(const SWindowEvent & event)
{
	if (event.event_type == EWindowEventType::eWE_MOUSE_POSITION_CHANGED)
	{
		tempMouseX = event.x;
		tempMouseY = event.y;
	}
	else if (event.event_type == EWindowEventType::eWE_MOUSE_BUTTON_PRESSED)
	{
		tempColor = 1.0;
	}
	else if (event.event_type == EWindowEventType::eWE_MOUSE_BUTTON_RELEASED)
	{
		tempColor = 0.0;
	}
}
