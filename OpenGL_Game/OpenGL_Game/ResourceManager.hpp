#pragma once
#include <map>
#include <vector>
#include "BasicEntity.hpp"
#include "Sprite.hpp"

class ResourceManager {
private:
	static std::map<BasicEntity*, Sprite*> spriteMap;
public:
	static void GenerateSprite(BasicEntity& entity, const char* vertexPath, const char* fragmentPath, const char* texturePath);
	static Sprite* GetSprite(BasicEntity& entity);
	static void DestroyResources();
};
