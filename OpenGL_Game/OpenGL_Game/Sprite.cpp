#include "Sprite.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


// without vertices
Sprite::Sprite(Shader* shader, Texture2D* texture) {
	// Initialize shader and texture
	this->shader = shader;
	this->texture = texture;
	if (shader == nullptr) {
		std::cout << "sprite was passed null ptr for shader" << std::endl;
		exit(-1000);
	}
	if (texture == nullptr) {
		std::cout << "sprite was passed null ptr for texture" << std::endl;
		exit(-1000);
	}
	modelMatrix = glm::mat4(1.0f);
}

Sprite::~Sprite() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Sprite::initBufferObjects(float* vertices) {
	// create buffers
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	// bind vao and load vbo data
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*30, vertices, GL_STATIC_DRAW);

	// set position and texture attributes
	GLsizei step = 5 * sizeof(float);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, step, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, step, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind vao
	glBindVertexArray(0);
}

void Sprite::updateVertices(float* vertices) {
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*30, vertices, GL_STATIC_DRAW);
}

void Sprite::useShader() {
	this->shader->use();
}

Shader* Sprite::getShader() {
	return shader;
}

Texture2D* Sprite::getTexture() {
	return texture;
}

int Sprite::getVertexArray() {
	return vao;
}

void Sprite::use() {
	texture->bind();
	shader->use();
}

void Sprite::setMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);
}
