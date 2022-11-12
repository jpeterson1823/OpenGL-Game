#include "Animation.hpp"
#include "ResourceManager.hpp"
#include <iostream>

Animation::Animation(Shader* s, Texture2D* t, int spriteWidth) : shader(s), texture(t), spriteWidth(spriteWidth) {
	currentSprite = 0;
	animationDelay = 0.125f;
	animationCounter = 0.0f;
}

Animation::~Animation() {
	for (Sprite* s : sprites)
		delete s;
}

void Animation::parseSprites(float spriteWidth, float spriteHeight, int row, int nSprites) {
	float xSpriteUnit = spriteWidth / texture->getWidth();
	float ySpriteUnit = spriteHeight / texture->getHeight();
	int y = ((float)texture->getWidth() / ySpriteUnit) - row - 1;
	for (int x = 0; x < nSprites; x++) {
		float xStart = x * xSpriteUnit;
		float yStart = (y + 1.0f) * ySpriteUnit;
		float xEnd = (x + 1.0f) * xSpriteUnit;
		float yEnd = y * ySpriteUnit;
		float v[30] = {
			// positions         // texture coords
			-0.5f,  0.5f, 0.0f,  xStart, yEnd, // top left 
			 0.5f,  0.5f, 0.0f,  xEnd, yEnd, // top right
			 0.5f, -0.5f, 0.0f,  xEnd, yStart, // bottom right

			 0.5f, -0.5f, 0.0f,  xEnd, yStart, // bottom right
			-0.5f, -0.5f, 0.0f,  xStart, yStart, // bottom left
			-0.5f,  0.5f, 0.0f,  xStart, yEnd  // top left 
		};
		Sprite* sprite = new Sprite(shader, texture);
		sprite->initBufferObjects(v);
		sprites.push_back(sprite);
	}
}

void Animation::animateIdle(float dt) {
	animationCounter += dt;
	if (animationCounter >= animationDelay) {
		animationCounter = 0;
		// bounds check
		if (++currentSprite >= sprites.size())
			currentSprite = 0;
	}
}

Shader* Animation::getShader() {
	return shader;
}

Texture2D* Animation::getTexture() {
	return texture;
}

std::vector<Sprite*> Animation::getSprites() {
	return sprites;
}

Sprite* Animation::getFrame(unsigned int index) {
	if (index < sprites.size())
		return sprites[index];
	else {
		std::cout << "Failed to get idle frame animation at specified index. Were the idle sprites parsed?" << std::endl;
		return nullptr;
	}
}

Sprite* Animation::getCurrentFrame() {
	return sprites[currentSprite];
}

void Animation::setAnimationDelay(float delay) {
	animationDelay = delay;
}
