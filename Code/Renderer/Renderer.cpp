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
	auto procaddr = m_pEnv->pSystem->getWindowProcAddress();
	if (!gladLoadGLLoader((GLADloadproc)procaddr))
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

	// Shader
	// Vertex Shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		m_pEnv->pLog->Log("CRenderer: Shader: Vertex: Compilation Failed.");
	}
	// ~Vertex Shader
	// Fragment Shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		m_pEnv->pLog->Log("CRenderer: Shader: Fragment: Compilation Failed.");
	}
	// ~Fragment Shader

	// Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		m_pEnv->pLog->Log("CRenderer: Shader: Program: Failed.");
	}

	glUseProgram(shaderProgram);
	// ~Shader Program

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// ~Shader

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
