#include "ResourceManager.hpp"

std::vector<Shader*> ResourceManager::shaders;
std::vector<Texture2D*> ResourceManager::textures;
std::vector<Animation*> ResourceManager::idleAnimations;
std::vector<Animation*> ResourceManager::activeAnimations;
std::map<unsigned short, Animation*> ResourceManager::idleAnimationMap;
std::map<unsigned short, Animation*> ResourceManager::activeAnimationMap;

Shader* ResourceManager::GenerateShader(const char* vertexPath, const char* fragmentPath) {
	Shader* s = new Shader(vertexPath, fragmentPath);
	shaders.push_back(s);
	return s;
}

Texture2D* ResourceManager::GenerateTexture2D(const char* texturePath, unsigned int texUnit) {
	Texture2D* t = new Texture2D(texturePath, true);
	textures.push_back(t);
	return t;
}

Animation* ResourceManager::GenerateIdleAnimation(BasicEntity* entity, Shader* shader, Texture2D* texture, int spriteWidth) {
	Animation* a = new Animation(shader, texture, spriteWidth);
	a->parseSprites(64, 64, 6, 5);
	idleAnimations.push_back(a);
	idleAnimationMap.insert(std::pair<unsigned short, Animation*>(entity->getID(), a));
	return a;
}

Animation* ResourceManager::GenerateActiveAnimation(BasicEntity* entity, Shader* shader, Texture2D* texture, int spriteWidth) {
	Animation* a = new Animation(shader, texture, spriteWidth);
	a->parseSprites(64, 64, 5, 4);
	activeAnimations.push_back(a);
	activeAnimationMap.insert(std::pair<unsigned short, Animation*>(entity->getID(), a));
	return a;
}


Animation* ResourceManager::GetAnimation(BasicEntity* entity) {
	std::map<unsigned short, Animation*>::iterator f;
	if (entity->isMoving()) {
		f = activeAnimationMap.find(entity->getID());
		if (f == activeAnimationMap.end())
			return nullptr;
	} else {
		f = idleAnimationMap.find(entity->getID());
		if (f == idleAnimationMap.end())
			return nullptr;
	}
	return f->second;
}

void ResourceManager::DestroyShader(unsigned int id) {
	for (int i = 0; i < shaders.size(); i++) {
		if (shaders[i]->getID() == id) {
			delete shaders[i];
			shaders.erase(shaders.begin() + i);
			break;
		}
	}
}

void ResourceManager::DestroyTexture2D(unsigned int id) {
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i]->getID() == id) {
			delete textures[i];
			textures.erase(textures.begin() + i);
			break;
		}
	}
}

void ResourceManager::DestroyResources() {
	// delete animations
	for (auto pair = activeAnimationMap.begin(); pair != activeAnimationMap.cend();) {
		delete pair->second;
		activeAnimationMap.erase(pair++);
	}
	activeAnimationMap.clear();
	for (auto pair = idleAnimationMap.begin(); pair != idleAnimationMap.cend();) {
		delete pair->second;
		idleAnimationMap.erase(pair++);
	}
	idleAnimationMap.clear();

	// delete shaders and textures
	for (Shader* s : shaders)
		delete s;
	for (Texture2D* t : textures)
		delete t;
}
