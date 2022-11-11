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
	Sprite(Shader* shader, Texture2D* texture);
	~Sprite();
	void initBufferObjects(float* vertices);
	void updateVertices(float* vertices);
	void useShader();
	int getVertexArray();
	Texture2D* getTexture();
	Shader* getShader();
	void use();
	void setMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};