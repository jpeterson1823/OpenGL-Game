#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "BackgroundTile.hpp"

class Background {
private:
	std::vector<BackgroundTile*> tiles;
	std::vector<glm::mat4> models;
public:
	Background();
	~Background();
	std::vector<BackgroundTile*> getTiles();
	std::vector<glm::mat4> getModels();
	void draw(glm::mat4 view, glm::mat4 projection);
};