#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "BackgroundTile.hpp"

BackgroundTile::BackgroundTile()
		: Sprite("graphics/shaders/background.vert", "graphics/shaders/background.frag", "graphics/textures/bg_big.png", false) {
	float* vertices = new float[30] {
		// positions         // texture coords
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top left 
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right

		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f // top left 
	};
	model = glm::mat4(1.0f);
	initBufferObjects(vertices);

	// delete vertices as they are now copied to the vbo
	delete[](vertices);
}

BackgroundTile::~BackgroundTile() {

}

void BackgroundTile::setPos(float x, float y) {
	model = glm::translate(model, glm::vec3(x, y, 0.0f));
}

void BackgroundTile::setModel(glm::mat4 model) {
	this->model = model;
}

void BackgroundTile::draw(glm::mat4 view, glm::mat4 projection) {
	this->Sprite::draw(model, view, projection);
}

