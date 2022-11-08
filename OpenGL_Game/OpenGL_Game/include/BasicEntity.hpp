#pragma once
#include <glm/glm.hpp>
#include "Sprite.hpp"
#include <vector>

class BasicEntity {
protected:
	float MAX_POS;
	float MIN_POS;
	float maxHealth;
	float health;
	float animationCounter;
	float animationDelay;
	bool living;
	bool moving;

	char currentSprite;
	std::vector<Sprite*> idleSprites;
	std::vector<Sprite*> activeSprites;
	glm::vec2 pos;
	glm::mat4 model;

	void die();

public:
	//BasicEntity(float maxHealth, const char* vertPath, const char* fragPath, std::string texFolderPath);
	BasicEntity(float maxHealth, Shader* shader, Texture2D* texture);
	~BasicEntity();

	// states
	bool isAlive();

	// setters
	void setAnimationDelay(float delay);
	void setPos(glm::vec2 pos);
	void setMoving();
	void setIdle();

	// getters
	Sprite& getSprite();
	glm::mat4& getModel();
	glm::vec2 getPos();
	
	// entity control
	float heal(float heal);
	float damage(float damage);
	void move(glm::vec2 vec);
	void animate(float dt);
};