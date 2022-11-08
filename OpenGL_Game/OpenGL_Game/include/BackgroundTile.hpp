#pragma once
#include <glm/glm.hpp>
#include "Sprite.hpp"

class BackgroundTile: public Sprite {
private:
	glm::mat4 model;

public:
	BackgroundTile();
	~BackgroundTile();
	void setPos(float x, float y);
	void draw(glm::mat4 view, glm::mat4 projection);
	void setModel(glm::mat4 model);
};