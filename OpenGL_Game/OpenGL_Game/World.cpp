#include "World.hpp"
#include "ResourceManager.hpp"
#include "EnemyEntity.hpp"
#include <GLFW/glfw3.h>

World::World() {
	// create player entity. Player will always be the first entity
	Player* p = new Player();
	Shader* s = ResourceManager::GenerateShader(p->VERT_PATH, p->FRAG_PATH);
	Texture2D* t = ResourceManager::GenerateTexture2D(p->SPRITE_SHEET_PATH);
	ResourceManager::GenerateIdleAnimation(p, s, t, 64);
	ResourceManager::GenerateActiveAnimation(p, s, t, 64);
	entities.push_back(p);
}

World::~World() {
	for (BasicEntity* entity : entities)
		delete(entity);
}

void World::turn(float dt) {
	for (BasicEntity* e : entities)
		ResourceManager::GetAnimation(e)->animateIdle(dt);
}

void World::spawnEnemy(glm::vec2 pos) {
	EnemyEntity* e = new EnemyEntity();
	Shader* s = ResourceManager::GenerateShader(e->VERT_PATH, e->FRAG_PATH);
	Texture2D* t = ResourceManager::GenerateTexture2D(e->SPRITE_SHEET_PATH);
	ResourceManager::GenerateIdleAnimation(e, s, t, 64);
	ResourceManager::GenerateActiveAnimation(e, s, t, 64);
	e->setPos(pos);
	entities.push_back(e);
}

Player* World::getPlayer() {
	return (Player*)entities[0];
}

std::vector<BasicEntity*> World::getEntities() {
	return entities;
}