#include "Tile.hpp"
#include <glm/gtc/matrix_transform.hpp>

Tile::Tile(glm::vec2 pos, Shader* shader, Texture2D* texture)
	: pos(pos), shader(shader), texture(texture) {
		// set and scale
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.25f));
	model = glm::translate(model, glm::vec3(pos.x-0.01, pos.y-0.01, 0.0f));

	// load sprites from sheet
	float imgWidth = 128.0f;
	float imgHeight = 128.0f;
	float spriteDimension = 16.0f;
	float xSpriteUnit = spriteDimension / imgWidth;
	float ySpriteUnit = spriteDimension / imgHeight;

	int y = 8;
	int x = 3;
	float xStart = x * xSpriteUnit;
	float yEnd = (y + 1.0f) * ySpriteUnit;
	float xEnd = (x + 1.0f) * xSpriteUnit;
	float yStart = y * ySpriteUnit;

	float v[30] = {
		// positions         // texture coords
		-0.5f,  0.5f, 0.0f,  xStart, yEnd, // top left 
		 0.5f,  0.5f, 0.0f,  xEnd, yEnd, // top right
		 0.5f, -0.5f, 0.0f,  xEnd, yStart, // bottom right

		 0.5f, -0.5f, 0.0f,  xEnd, yStart, // bottom right
		-0.5f, -0.5f, 0.0f,  xStart, yStart, // bottom left
		-0.5f,  0.5f, 0.0f,  xStart, yEnd  // top left 
	};

	sprite = new Sprite(shader, texture);
	sprite->initBufferObjects(v);
}

Tile::~Tile() {
	delete sprite;
}

Sprite* Tile::getSprite() {
	return sprite;
}

glm::vec2& Tile::getPos() {
	return pos;
}

glm::mat4& Tile::getModel() {
	return model;
}
