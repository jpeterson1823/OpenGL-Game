#include "World.hpp"
#include "ResourceManager.hpp"
#include "EnemyEntity.hpp"

World::World() {
	// create player entity. Player will always be the first entity
	Player* p = new Player;
	ResourceManager::GenerateSprite(*p, p->VERT_PATH, p->FRAG_PATH, p->SPRITE_SHEET_PATH);
	entities.push_back(p);
}

World::~World() {
	for (BasicEntity* entity : entities)
		delete(entity);
}

void World::turn(float dt) {
}

void World::spawnEnemy(glm::vec2 pos) {
	EnemyEntity* e = new EnemyEntity();
	ResourceManager::GenerateSprite(*e, e->VERT_PATH, e->FRAG_PATH, e->SPRITE_SHEET_PATH);
	e->setPos(pos);
	entities.push_back(e);
}

Player* World::getPlayer() {
	return (Player*)entities[0];
}

std::vector<BasicEntity*> World::getEntities() {
	return entities;
}