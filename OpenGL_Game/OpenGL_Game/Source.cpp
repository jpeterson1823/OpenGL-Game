#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "stb_image.h"

#include "Window.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "ResourceManager.hpp"
#include "Line.hpp"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const unsigned int SCR_WIDTH  = 1920;
const unsigned int SCR_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* w, int width, int height);
void processInput(GLFWwindow* w, Camera& camera, Player& player);
Line getMouseTrace(Window& window, Player& player, Shader& lineShader);

int main(int argc, char* argv[]) {
	// enable memory leak check
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// init glfw and create window obj
	glfwInit();

	// create window
	Window window(SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// set window's frame buffer callback and input handler
	glfwSetFramebufferSizeCallback(window.ptr(), framebuffer_size_callback);

	Camera camera;
	World world;
	Shader lineShader("graphics/shaders/line.vert", "graphics/shaders/line.frag");
	Renderer::Initialize(&camera, SCR_WIDTH, SCR_HEIGHT);

	// spawn test dummy
	world.spawnEnemy(glm::vec2(0.0f, 0.5f));

	// window loop
	float tickDelay = 1.0f/120.0f;
	float tickCounter = 0.0f;
	float currentFrame;
	float frameCounter = 0.0f;
	int frames = 0;
	while (!glfwWindowShouldClose(window.ptr())) {
		// calc dt
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		tickCounter += deltaTime;
		frameCounter += deltaTime;

		// process input
		processInput(window.ptr(), camera, *world.getPlayer());
		Line mouseTrace = getMouseTrace(window, *world.getPlayer(), lineShader);

		// rendering settings
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (tickCounter >= tickDelay) {
			tickCounter = 0;
		}
		world.turn(deltaTime);
		Renderer::RenderWorld(world);
		Renderer::DrawLine(mouseTrace);
		Renderer::Update();

		// check & call events + swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window.ptr());
		frames++;

		if (frameCounter >= 1.0f) {
			std::cout << frames << "FPS" << std::endl;
			frames = 0;
			frameCounter = 0.0f;
		}
	}
	
	ResourceManager::DestroyResources();
	window.terminate();

	//_CrtDumpMemoryLeaks();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* w, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* w, Camera& camera, Player& player) {
	float cameraSpeed = 0.5f * deltaTime;
	bool playerMoved = false;

	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(w, true);

	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
		camera.move(cameraSpeed * camera.getUp());
		player.move(cameraSpeed * camera.getUp());
	}
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {
		camera.move(-cameraSpeed * camera.getUp());
		player.move(-cameraSpeed * camera.getUp());
	}
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS) {
		camera.move(-glm::cross(camera.getDirection(), camera.getUp()) * cameraSpeed);
		player.move(-glm::cross(camera.getDirection(), camera.getUp()) * cameraSpeed);
		player.setFacingLeft();
		playerMoved = true;
	}
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS) {
		camera.move(glm::cross(camera.getDirection(), camera.getUp()) * cameraSpeed);
		player.move(glm::cross(camera.getDirection(), camera.getUp()) * cameraSpeed);
		player.setFacingRight();
		playerMoved = true;
	}

	if (playerMoved)
		player.setMoving();
	else
		player.setIdle();

	// debug stuffs
	if (glfwGetKey(w, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.move(-camera.getDirection() * (cameraSpeed * 10));
	if (glfwGetKey(w, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		camera.move(camera.getDirection() * (cameraSpeed * 10));
}

Line getMouseTrace(Window& window, Player& player, Shader& lineShader) {
	// get cursor position
	double xpos, ypos;
	glfwGetCursorPos(window.ptr(), &xpos, &ypos);

	// perform literal magic to convert to world coords
	glm::mat4 temp = glm::inverse(Renderer::GetProjection() * Renderer::GetView());
	glm::vec4 v = 2.0f * (glm::vec4(2.0f*xpos/SCR_WIDTH - 1.0f, 1.0f - 2.0f*ypos/SCR_HEIGHT, 0.0f, 1.0f) * temp);
	
	// create line to be rendered
	return Line(player.getPos(), glm::vec2(v.x + player.getPos().x, v.y + player.getPos().y), &lineShader);
}
