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
	bool living;
	bool moving;
	bool facingRight;
	unsigned short id;

	glm::vec2 pos;
	glm::mat4 model;

	void die();

public:
	//BasicEntity(float maxHealth, const char* vertPath, const char* fragPath, std::string texFolderPath);
	BasicEntity(float maxHealth, unsigned short id);
	~BasicEntity();

	// states
	bool isAlive();
	bool isMoving();
	bool isFacingRight();

	// setters
	void setPos(glm::vec2 pos);
	void setMoving();
	void setIdle();
	void setFacingRight();
	void setFacingLeft();

	// getters
	glm::mat4& getModel();
	glm::vec2 getPos();
	unsigned short getID();
	
	// entity control
	float heal(float heal);
	float damage(float damage);
	void move(glm::vec2 vec);
};