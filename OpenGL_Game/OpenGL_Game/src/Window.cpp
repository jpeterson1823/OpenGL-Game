#include <iostream>
#include "Window.hpp"

// Creates a GLFW window object
Window::Window(unsigned int width, unsigned int height)
		: width(width), height(height) {
	// set window settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window pointer
	//self = glfwCreateWindow(width, height, "Name TBD", glfwGetPrimaryMonitor(), NULL);
	self = glfwCreateWindow(width, height, "Name TBD", NULL, NULL);
	if (self == NULL) {
		std::cout << "[ERROR] Failed to create GLFW window." << std::endl;
		glfwTerminate();
		exit(-1);
	}
	// set context
	glfwMakeContextCurrent(self);

	// init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[ERROR] Failed to initialize GLAD." << std::endl;
		exit(-1);
	}
	// set viewport
	glViewport(0, 0, width, height);
}


Window::~Window() {

}

void Window::terminate() {
	glfwTerminate();
}

GLFWwindow* Window::ptr() {
	return this->self;
}