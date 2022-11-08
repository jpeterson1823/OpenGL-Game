#pragma once

#include "Shader.hpp"
#include <glm/glm.hpp>
#include <vector>

class Line {
private:
	Shader* shader;
	std::vector<float> vertices;
	unsigned int vao, vbo;
	glm::vec3 startPoint;
	glm::vec3 endPoint;
	glm::vec3 color;
public:
	Line(glm::vec2 start, glm::vec2 end, Shader* shader);
	~Line();
	void draw(glm::mat4 view, glm::mat4 projection);
};