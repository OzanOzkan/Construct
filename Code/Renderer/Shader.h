#pragma once

#include <System/ISystem.h>
#include <string>

class CShader
{
public:
	CShader(SEnvironment* env, const char* vertexSourceFile, const char* fragmentSourceFile);
	virtual ~CShader() {}

	// use/activate the shader
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void set4F(const std::string &name, const float& f0, const float& f1, const float& f2, const float& f3) const;
	
	unsigned int getID() { return m_ID; }

private:
	SEnvironment * m_pEnv;
	unsigned int m_ID;
};