#include "BasicEntity.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <filesystem>

BasicEntity::BasicEntity(float maxHealth, Shader* shader, Texture2D* texture) {
	// set min and max position for entities
	MAX_POS = 100.0;
	MIN_POS = -MAX_POS;

	// set max health and set alive
	if (maxHealth > 0)
		this->maxHealth = maxHealth;
	else
		this->maxHealth = 100.0f;
	health = this->maxHealth;
	living = true;
	moving = false;

	// set initial position to origin
	pos = glm::vec2(0.0f);
	// set model matrix to identity
	model = glm::mat4(1.0f);

	// load sprites from sheet
	float imgWidth = 576.0f;
	float imgHeight = 512.0f;
	float spriteDimension = 64.0f;
	float xSpriteUnit = spriteDimension / imgWidth;
	float ySpriteUnit = spriteDimension / imgHeight;

	int y = 6;
	for (int x = 0; x < 5; x++) {
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
		
		Sprite* s = new Sprite(shader, texture);
		s->initBufferObjects(v);
		idleSprites.push_back(s);
	}

	// set current sprite, animation counter, and default animation delay
	currentSprite = 0;
	animationCounter = 0.0f;
	animationDelay = 0.5f;
}

BasicEntity::~BasicEntity() {
	delete(idleSprites[0]->getShader());
	delete(idleSprites[0]->getTexture());
	for (Sprite* sprite : idleSprites)
		delete(sprite);
	for (Sprite* sprite : activeSprites)
		delete(sprite);
}

void BasicEntity::die() {
	health = 0.0f;
	living = false;
}

bool BasicEntity::isAlive() {
	return living;
}

void BasicEntity::setAnimationDelay(float delay) {
	animationDelay = delay;
}

void BasicEntity::setPos(glm::vec2 pos) {
	this->pos = pos;
}

void BasicEntity::setMoving() {
	moving = true;
}

void BasicEntity::setIdle() {
	moving = false;
}


Sprite& BasicEntity::getSprite() {
	return *idleSprites[currentSprite];
}

glm::mat4& BasicEntity::getModel() {
	return model;
}

glm::vec2 BasicEntity::getPos() {
	return pos;
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

void BasicEntity::animate(float dt) {
	animationCounter += dt;
	if (animationCounter >= animationDelay) {
		animationCounter = 0.0f;
		currentSprite++;
		if (currentSprite >= idleSprites.size())
			currentSprite = 0;
	}
}
