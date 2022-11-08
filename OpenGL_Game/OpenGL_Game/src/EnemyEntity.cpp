#include "EnemyEntity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const char* EnemyEntity::VERT_PATH = "graphics/shaders/entity.vert";
const char* EnemyEntity::FRAG_PATH = "graphics/shaders/entity.frag";
const char* EnemyEntity::SPRITE_SHEET_PATH = "graphics/textures/entities/player/sheet.png";


EnemyEntity::EnemyEntity() : BasicEntity(100.0f, new Shader(VERT_PATH, FRAG_PATH), new Texture2D(SPRITE_SHEET_PATH, true)) {
	// scale model down a little bit
	model = glm::scale(model, glm::vec3(0.5f));
	animationDelay = 0.3f;
}
