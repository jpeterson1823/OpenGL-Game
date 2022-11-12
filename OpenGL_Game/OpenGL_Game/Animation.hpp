#pragma once

#include <vector>
#include "Sprite.hpp"

class Animation {
private:
	Shader* shader;
	Texture2D* texture;
	int spriteWidth;
	std::vector<Sprite*> sprites;
	int currentSprite;
	float animationCounter;
	float animationDelay;


public:
	Animation(Shader* s, Texture2D* t, int spriteWidth);
	~Animation();
	void parseSprites(float spriteWidth, float spriteHeight, int row, int nSprites);

	void animateIdle(float dt);
	Shader* getShader();
	Texture2D* getTexture();
	std::vector<Sprite*> getSprites();
	Sprite* getFrame(unsigned int index);
	Sprite* getCurrentFrame();
	void setAnimationDelay(float delay);
};
