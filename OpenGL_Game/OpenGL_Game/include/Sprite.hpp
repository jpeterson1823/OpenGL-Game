#pragma once
#include "Shader.hpp"
#include "Texture2D.hpp"

class Sprite {
protected:
	unsigned int vao;
	unsigned int vbo;
	Shader* shader;
	Texture2D* texture;
	glm::mat4 modelMatrix;

public:
	Sprite();
	Sprite(Shader* shader, Texture2D* texture);
	~Sprite();
	void initBufferObjects(float* vertices);
	void updateVertices(float* vertices);
	void useShader();
	int getVertexArray();
	Texture2D* getTexture();
	Shader* getShader();
};