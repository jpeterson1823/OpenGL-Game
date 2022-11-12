#include "BasicEntity.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <filesystem>

BasicEntity::BasicEntity(float maxHealth) {
	// set min and max position for entities
	MAX_POS = 100.0;
	MIN_POS = -MAX_POS;

	// set max health and set alive
	if (maxHealth > 0)
		this->maxHealth = maxHealth;
	else
		this->maxHealth = 100.0f;
	this->id = id;
	health = this->maxHealth;
	living = true;
	moving = false;
	facingRight = true;

	// set initial position to origin
	pos = glm::vec2(0.0f);
	// set model matrix to identity
	model = glm::mat4(1.0f);
}

BasicEntity::~BasicEntity() {
}

void BasicEntity::die() {
	health = 0.0f;
	living = false;
}

bool BasicEntity::isAlive() {
	return living;
}

bool BasicEntity::isMoving() {
	return moving;
}

bool BasicEntity::isFacingRight() {
	return facingRight;
}

glm::mat4& BasicEntity::getModel() {
	return model;
}

glm::vec2 BasicEntity::getPos() {
	return pos;
}

unsigned short BasicEntity::getID() {
	return id;
}

void BasicEntity::setPos(glm::vec2 pos) {
	this->pos = pos;
}

void BasicEntity::setMoving() {
	if (!moving)
		moving = true;
}

void BasicEntity::setIdle() {
	if (moving)
		moving = false;
}

void BasicEntity::setFacingRight() {
	if (!facingRight)
		facingRight = true;
}

void BasicEntity::setFacingLeft() {
	if (facingRight)
		facingRight = false;
}

float BasicEntity::heal(float heal) {
	health += heal;
	if (health > maxHealth)
		health = maxHealth;
	return health;
}

float BasicEntity::damage(float damage) {
	health -= damage;
	
	// if no health remains, die
	if (health <= 0.0f)
		die();

	return health;
}

void BasicEntity::move(glm::vec2 vec) {
	pos += vec;
	if (pos.x > MAX_POS)
		pos.x = MAX_POS;
	if (pos.x < MIN_POS)
		pos.x = MIN_POS;

	if (pos.y > MAX_POS)
		pos.y = MAX_POS;
	if (pos.y < MIN_POS)
		pos.y = MIN_POS;
}
