#include "Texture.h"

#include <stdexcept>
#include "Matrix.h"
#include "stb_image.h"

Texture::Texture(const std::string& filename)
{
	int width, height, components;
	unsigned char* const image = stbi_load(filename.c_str(), &width, &height, &components, STBI_rgb_alpha);
	if (!image) throw std::runtime_error("Could not load " + filename + ".");
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(image);
}

void Texture::draw(ShaderProgram& program)
{	
	const float hh = height/2;
	const float hw = width/2;
	glBindTexture(GL_TEXTURE_2D, id);
	float vertices[] = {-hw, -hh,
	                    hw, -hh,
	                    hw, hh,
	                    -hw, -hh,
	                    hw, hh,
	                    -hw, hh};
	glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program.positionAttribute);
	float texCoords[] = {0.0, 1.0,
	                     1.0, 1.0,
	                     1.0, 0.0,
	                     0.0, 1.0,
	                     1.0, 0.0,
	                     0.0, 0.0};
	glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program.texCoordAttribute);
	Matrix modelMatrix;
	modelMatrix.setPosition(x, y, 0.0f);
	modelMatrix.setRotation(rotation);
	program.setModelMatrix(modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(program.positionAttribute);
	glDisableVertexAttribArray(program.texCoordAttribute);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}
