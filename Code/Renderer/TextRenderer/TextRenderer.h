#pragma once

#include <System/ISystem.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>


struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

class CTextRenderer
{
public:
	CTextRenderer(SEnvironment* env);
	~CTextRenderer() {}

	void renderText(const std::string& text, float x, float y, float scale);

private:
	void loadFont();

private:
	SEnvironment * m_pEnv;
	FT_Library m_freeTypeLib;

	std::map<GLchar, Character> m_characters;

	GLuint VAO, VBO;
};