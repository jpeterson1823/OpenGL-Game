#pragma once

#include <glm/glm.hpp>
#include "World.hpp"
#include "BasicEntity.hpp"
#include "Camera.hpp"
#include "Line.hpp"
#include "Tile.hpp"

class Renderer {
private:
	static Camera* camera;
	static glm::mat4 projection;
	
public:
	static void Initialize(Camera* camera, float src_width, float src_height);
	static void RenderEntity(BasicEntity& e);
	static void RenderWorld(World& world);
	static void RenderTile(Tile& tile);
	static void DrawLine(Line& line);
	static glm::mat4 GetView();
	static glm::mat4 GetProjection();
	static void Update();
};