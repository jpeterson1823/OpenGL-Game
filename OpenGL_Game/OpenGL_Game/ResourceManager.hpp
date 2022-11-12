#pragma once
#include <map>
#include <vector>
#include "BasicEntity.hpp"
#include "Animation.hpp"

class ResourceManager {
private:
	static std::vector<Shader*> shaders;
	static std::vector<Texture2D*> textures;
	static std::vector<Animation*> idleAnimations;
	static std::vector<Animation*> activeAnimations;
	static std::map<BasicEntity*, Animation*> idleAnimationMap;
	static std::map<BasicEntity*, Animation*> activeAnimationMap;
public:
	static Shader* GenerateShader(const char* vertexPath, const char* fragmentPath);
	static Texture2D* GenerateTexture2D(const char* texturePath, unsigned int texUnit=GL_TEXTURE0);
	static Animation* GetAnimation(BasicEntity* entity);
	static Animation* GenerateActiveAnimation(BasicEntity* entity, Shader* shader, Texture2D* texture, int spriteWidth);
	static Animation* GenerateIdleAnimation(BasicEntity* entity, Shader* shader, Texture2D* texture, int spriteWidth);
	static void DestroyShader(unsigned int id);
	static void DestroyTexture2D(unsigned int id);
	static void DestroyResources();
};
