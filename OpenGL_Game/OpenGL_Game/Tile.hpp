#pragma once

#include "Sprite.hpp"

class Tile {
private:
	Shader* shader;
	Texture2D* texture;
	Sprite* sprite;
	glm::vec2 pos;
	glm::mat4 model;

public:
	Tile(glm::vec2 pos, Shader* shader, Texture2D* texture);
	~Tile();

	Sprite* getSprite();
	glm::vec2& getPos();
	glm::mat4& getModel();
};