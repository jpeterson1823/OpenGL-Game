#include "Renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.hpp"
#include "Animation.hpp"
#include <iostream>

// for test func
#include "Sprite.hpp"
#include "Texture2D.hpp"

Camera* Renderer::camera = nullptr;
glm::mat4 Renderer::projection = glm::mat4(1.0f);

void Renderer::Initialize(Camera* cam, float scr_width, float scr_height) {
	// save camera pointer
	camera = cam;
	// set default projection matrix
	projection = glm::perspective(glm::radians(camera->getFov()), scr_width / scr_height, 0.1f, 1000.0f);
}

void Renderer::RenderEntity(BasicEntity& e) {
	glm::vec3 pos  = glm::vec3(e.getPos(), 0.0f);
	glm::mat4 view = glm::translate(camera->view, pos);

	Animation* a = ResourceManager::GetAnimation(&e);
	a->getTexture()->bind();
	a->getShader()->use();
	a->getShader()->setMVP(e.getModel(), view, projection);

	if (e.isFacingRight())
		a->getShader()->setInt("facingRight", 1);
	else
		a->getShader()->setInt("facingRight", 0);

	glBindVertexArray(a->getCurrentFrame()->getVertexArray());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::RenderWorld(World& world) {
	for (BasicEntity* e : world.getEntities())
		Renderer::RenderEntity(*e);
}

void Renderer::Update() {
	camera->updateView();
}

void Renderer::DrawLine(Line& line) {
	line.draw(camera->view, projection);
}

glm::mat4 Renderer::GetView() {
	return camera->view;
}

glm::mat4 Renderer::GetProjection() {
	return projection;
}

