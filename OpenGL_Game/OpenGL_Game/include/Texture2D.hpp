#pragma once
#include <glad/glad.h>

class Texture2D {
private:
	unsigned int id;
	unsigned int texUnit;

public:
	Texture2D(const char* path, bool alphaEnabled, unsigned int texUnit=GL_TEXTURE0);
	~Texture2D();
	unsigned int getID();
	unsigned int getTexUnit();
	void bind();
};