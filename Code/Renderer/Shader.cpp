/* Copyright (C) 2019 Ozan Ozkan
* All of the implementations are experimental and subject to change.
*/

#include "Shader.h"

#include <ILog.h>

#include <glad/glad.h>
#include <GL/GL.h>

/////////////////////////////////////////////////
CShader::CShader(SEnvironment * env, const char* vertexSourceFile, const char* fragmentSourceFile)
	:m_pEnv(env)
{
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// Vertex Shader
	// Read vertex shader source file
	auto buff = m_pEnv->pSystem->getFileManager()->readFile(vertexSourceFile);
	const char* vertexSource = buff.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		m_pEnv->pLog->Log("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
	};

	// Fragment Shader
	// Read fragment shader source file
	buff = m_pEnv->pSystem->getFileManager()->readFile(fragmentSourceFile);
	const char* fragmentSource = buff.c_str();

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		m_pEnv->pLog->Log("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
	};

	// shader Program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	// print linking errors if any
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		m_pEnv->pLog->Log("ERROR::SHADER::PROGRAM::LINKING_FAILED");
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

/////////////////////////////////////////////////
void CShader::use()
{
	glUseProgram(m_ID);
}

/////////////////////////////////////////////////
void CShader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}

/////////////////////////////////////////////////
void CShader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

/////////////////////////////////////////////////
void CShader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void CShader::set4F(const std::string &name, const float & f0, const float & f1, const float & f2, const float & f3) const
{
	glUniform4f(glGetUniformLocation(m_ID, name.c_str()), f0, f1, f2, f3);
}
