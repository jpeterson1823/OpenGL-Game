#include "ResourceManager.hpp"

std::map<BasicEntity*, Sprite*> ResourceManager::spriteMap;

void ResourceManager::GenerateSprite(BasicEntity& entity, const char* vertexPath, const char* fragmentPath, const char* texturePath) {
	Shader* s = new Shader(vertexPath, fragmentPath);
	Texture2D* t = new Texture2D(texturePath, true);

	float imgWidth = 576.0f;
	float imgHeight = 512.0f;
	float spriteDimension = 64.0f;
	float xSpriteUnit = spriteDimension / imgWidth;
	float ySpriteUnit = spriteDimension / imgHeight;

	float x = 0;
	float y = 6;
	float xStart = x * xSpriteUnit;
	float yEnd = (y + 1.0f) * ySpriteUnit;
	float xEnd = (x + 1.0f) * xSpriteUnit;
	float yStart = y * ySpriteUnit;

	float v[30] = {
		// positions         // texture coords
		-0.5f,  0.5f, 0.0f,  xStart, yEnd, // top left 
		 0.5f,  0.5f, 0.0f,  xEnd, yEnd, // top right
		 0.5f, -0.5f, 0.0f,  xEnd, yStart, // bottom right

		 0.5f, -0.5f, 0.0f,  xEnd, yStart, // bottom right
		-0.5f, -0.5f, 0.0f,  xStart, yStart, // bottom left
		-0.5f,  0.5f, 0.0f,  xStart, yEnd  // top left 
	};

	/*for (int x = 0; x < 5; x++) {
		float xStart = x * xSpriteUnit;
		float yEnd = (y + 1.0f) * ySpriteUnit;
		float xEnd = (x + 1.0f) * xSpriteUnit;
		float yStart = y * ySpriteUnit;

		idleSprites.push_back(sprite);
	}*/
	Sprite* sprite = new Sprite(s, t);
	sprite->initBufferObjects(v);
	spriteMap.insert(std::pair<BasicEntity*, Sprite*>(&entity, sprite));
}

Sprite* ResourceManager::GetSprite(BasicEntity& entity) {
	auto f = spriteMap.find(&entity);
	if (f == spriteMap.end())
		return nullptr;
	return f->second;
}

void ResourceManager::DestroyResources() {
	for (auto pair = spriteMap.begin(); pair != spriteMap.cend();) {
		delete pair->second->getShader();
		delete pair->second->getTexture();
		delete pair->second;
		spriteMap.erase(pair++);
	}
	spriteMap.clear();
}
