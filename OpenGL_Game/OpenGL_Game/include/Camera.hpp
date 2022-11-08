#pragma once
#include <glm/glm.hpp>

const static glm::vec3 ORIGIN = glm::vec3(0.0f, 0.0f, 0.0f);

class Camera {
private:
	float MAX_POS;
	float MIN_POS;
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	float fov;

	bool __firstMouse;
	float __lastX;
	float __lastY;

public:
	glm::mat4 view;

	Camera();
	void move(glm::vec3 vec);
	void updateView();

	void setPos(glm::vec3 pos);
	void setDirection(glm::vec3 direction);

	float getFov();
	glm::vec3 getUp();
	glm::vec3 getPos();
	glm::vec3 getDirection();
};