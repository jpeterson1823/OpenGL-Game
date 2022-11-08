#pragma once

#include <glm/glm.hpp>
#include "World.hpp"
#include "BasicEntity.hpp"
#include "Camera.hpp"
#include "Line.hpp"
#include "Tile.hpp"

class Renderer {
private:
	Camera* camera;
	glm::mat4 projection;
	
public:
	Renderer(Camera* camera, float src_width, float src_height);
	void renderEntity(BasicEntity& e);
	void renderWorld(World& world);
	void renderSprite(Sprite& sprite);
	void renderTile(Tile& tile);
	void drawLine(Line& line);
	glm::mat4 getView();
	glm::mat4 getProjection();
	void update();
};