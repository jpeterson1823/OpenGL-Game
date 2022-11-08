#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

// creates a camera object
Camera::Camera() {
	MAX_POS = 100.0;
	MIN_POS = -MAX_POS;
	// set default fov
	fov = 45.0f;

	// set view matrix to identity matrix
	view = glm::mat4(1.0f);

	// set camera's initial position (ORIGIN + [0, 0, 1]);
	pos = glm::vec3(0.0f, 0.0f, 2.0f);

	// set camera up vector
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	/* 
	set camera front vector.
		front.z is negative due the direction vector of the camera points towards the camera's face,
		so when flipped, the "front" vector points away from the camera's face, i.e. in the
		direction the camera is facing.
	*/
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	// set camera looking at origin
	updateView();
}

void Camera::move(glm::vec3 vec) {
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

void Camera::updateView() {
	view = glm::lookAt(
		pos,
		pos + front,
		up
	);
}

// getters and setters
glm::vec3 Camera::getPos() {
	return this->pos;
}
glm::vec3 Camera::getDirection() {
	return this->front;
}
glm::vec3 Camera::getUp() {
	return this->up;
}
float Camera::getFov() {
	return this->fov;
}
void Camera::setPos(glm::vec3 pos) {
	this->pos = pos;
	updateView();
}
void Camera::setDirection(glm::vec3 direction) {
	this->front = direction;
	updateView();
}