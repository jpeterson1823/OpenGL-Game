#include "Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>

// for test func
#include "Sprite.hpp"
#include "Texture2D.hpp"

Renderer::Renderer(Camera* camera, float scr_width, float scr_height) : camera(camera) {
	// set default projection matrix
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(camera->getFov()), scr_width / scr_height, 0.1f, 1000.0f);
}

void Renderer::renderEntity(BasicEntity& e) {
	glm::vec3 pos  = glm::vec3(e.getPos(), 0.0f);
	glm::mat4 view = glm::translate(camera->view, pos);
	Shader* shader = e.getSprite().getShader();

	e.getSprite().getTexture()->bind();
	shader->use();
	shader->setMat4("model", e.getModel());
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);
	glBindVertexArray(e.getSprite().getVertexArray());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::renderWorld(World& world) {
	for (BasicEntity* e : world.getEntities())
		renderEntity(*e);
}

void Renderer::update() {
	camera->updateView();
}

void Renderer::drawLine(Line& line) {
	line.draw(camera->view, projection);
}

glm::mat4 Renderer::getView() {
	return camera->view;
}

glm::mat4 Renderer::getProjection() {
	return projection;
}

void Renderer::renderSprite(Sprite& sprite) {
	glm::mat4 model = glm::mat4(1.0f);
	Shader* shader = sprite.getShader();
	sprite.getTexture()->bind();
	shader->use();
	shader->setMat4("model", model);
	shader->setMat4("view", camera->view);
	shader->setMat4("projection", projection);
	glBindVertexArray(sprite.getVertexArray());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
