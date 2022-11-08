#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
	unsigned int width;
	unsigned int height;
	GLFWwindow* self;

public:
	Window(unsigned int width, unsigned int height);
	~Window();
	void terminate();
	GLFWwindow* ptr();
};