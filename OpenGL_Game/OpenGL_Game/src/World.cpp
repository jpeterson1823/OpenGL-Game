#include "World.hpp"
#include "EnemyEntity.hpp"

World::World() {
	// create player entity. Player will always be the first entity
	entities.push_back(new Player());
}

World::~World() {
	for (BasicEntity* entity : entities)
		delete(entity);
}

void World::turn(float dt) {
	animateEntities(dt);
}

void World::animateEntities(float dt) {
	for (BasicEntity* e : entities)
		e->animate(dt);
}

void World::spawnEnemy(glm::vec2 pos) {
	EnemyEntity* e = new EnemyEntity();
	e->setPos(pos);
	entities.push_back(e);
}

Player* World::getPlayer() {
	return (Player*)entities[0];
}

std::vector<BasicEntity*> World::getEntities() {
	return entities;
}