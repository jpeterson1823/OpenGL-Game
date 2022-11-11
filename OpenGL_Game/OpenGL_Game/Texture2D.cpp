#include "Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GLFW/glfw3.h>
#include <iostream>

Texture2D::Texture2D(const char* path, bool alphaEnabled, unsigned int texUnit) {
	// set texture unit
	this->texUnit = texUnit;

	// generate and bind this texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// set wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// set filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load image and generate texture data
	int width, height, nrChannels;
	unsigned char* data;
	stbi_set_flip_vertically_on_load(true);
	if (alphaEnabled)
		data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);
	else
		data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb);
	if (data) {
		if (alphaEnabled) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			std::cout << "RGBA IMAGE MODE SELECTED\n";
		}
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "[ERROR] Failed to load texture! PATH='";
		std::cout << path;
		std::cout << "'" << std::endl;
	}
	// free image data
	stbi_image_free(data);
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &id);
}

unsigned int Texture2D::getID() {
	return this->id;
}

unsigned int Texture2D::getTexUnit() {
	return this->texUnit;
}

void Texture2D::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}
