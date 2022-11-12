#pragma once

#include "BasicEntity.hpp"
#include <vector>

class Player : public BasicEntity{
private:
public:
	static const char* VERT_PATH;
	static const char* FRAG_PATH;
	static const char* SPRITE_SHEET_PATH;
	Player(unsigned short id);
};