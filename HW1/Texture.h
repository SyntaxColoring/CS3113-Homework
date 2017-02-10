#pragma once

#include <string>
#include <GL/glew.h>

#include "ShaderProgram.h"

class Texture
{
	GLuint id;
	public:
	explicit Texture(const std::string& filename);
	~Texture();
	void draw(ShaderProgram& program);
	
	float width = 1.0;
	float height = 1.0;
	float x = 0.0;
	float y = 0.0;
	float rotation = 0.0;
};
