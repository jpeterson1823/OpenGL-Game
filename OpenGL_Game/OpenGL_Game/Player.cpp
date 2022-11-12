#include <glm/gtc/matrix_transform.hpp>
#include "Player.hpp"

const char* Player::VERT_PATH = "graphics/shaders/entity.vert";
const char* Player::FRAG_PATH = "graphics/shaders/entity.frag";
const char* Player::SPRITE_SHEET_PATH = "graphics/textures/entities/player.png";

Player::Player(unsigned short id) : BasicEntity(100.0f, id) {
	// scale model down
	model = glm::scale(model, glm::vec3(0.25f));
}
