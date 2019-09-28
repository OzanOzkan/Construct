#include "Renderer.h"

#include <System/ISystem.h>
#include <ILog.h>

#include <glad/glad.h>
#include <GL/GL.h>
#include "Shader.h"

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
	auto procaddr = m_pEnv->pSystem->getWindowProcAddress();
	if (!gladLoadGLLoader((GLADloadproc)procaddr))
		m_pEnv->pLog->Log("CGLFWWindow::openWindow: Failed to load GLAD.");


	m_pEnv->pSystem->registerWindowEvents(this);

	glViewport(0, 0, 800, 600);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glOrtho(0.0, 800.0, 0.0, 600.0, 0.0, 1.0);

	// Compile default shader
	m_defaultShader = std::make_unique<CShader>(m_pEnv,
		"C:/Users/Ozann/Documents/GitHub/ProjectO01/Assets/Shaders/default.vs",
		"C:/Users/Ozann/Documents/GitHub/ProjectO01/Assets/Shaders/default.fs");

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
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float timeValue = m_pEnv->pSystem->getTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	
	m_defaultShader->set4F("vertexColor", 0.0f, greenValue, 0.f, 1.0f);
	m_defaultShader->use();

	glDrawArrays(GL_TRIANGLES, 0, 3);
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
