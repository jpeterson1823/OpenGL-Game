#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Player.hpp"
#include "BasicEntity.hpp"

class World {
private:
	std::vector<BasicEntity*> entities;
	std::vector<unsigned short> activeIDs;
	
public:
	World();
	~World();

	void turn(float dt);
	void spawnEnemy(glm::vec2 pos);

	Player* getPlayer();
	std::vector<BasicEntity*> getEntities();
};