#include "Line.hpp"
#include <glad/glad.h>
#include <iostream>

Line::Line(glm::vec2 start, glm::vec2 end, Shader* shader) {
	startPoint = glm::vec3(start, 0.0f);
	endPoint = glm::vec3(end, 0.0f);
	color = glm::vec3(1.0f);

	this->shader = shader;

	vertices = {
		start.x, start.y, 0.0f,
		end.x, end.y, 0.0f
	};
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

Line::~Line() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Line::draw(glm::mat4 view, glm::mat4 projection) {
	shader->use();
	shader->setVec3("color", color);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}