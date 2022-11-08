#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Background.hpp"

Background::Background() {
	/*BackgroundTile* centerTile = new BackgroundTile();
	centerTile->setModel(glm::scale(glm::mat4(1.0f), glm::vec3(40.0f)));
	tiles.push_back(centerTile);*/


	/*
	// generate tile next to center tile
	BackgroundTile* next = new BackgroundTile();
	next->setModel(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	tiles.push_back(next);*/

	// generate 32x32
	/*
	int dimension = 32;
	BackgroundTile* tile;
	for (int y = -dimension/2; y < dimension/2+1; y++) {
		for (int x = -dimension/2; x < dimension/2+1; x++) {
			//std::cout << "Placing tile at (" << (float)x << ',' << (float)y << ")\n";
			tile = new BackgroundTile();
			tile->setModel(glm::translate(glm::mat4(1.0f), glm::vec3((float)x, (float)y, 0.0f)));
			tiles.push_back(tile);
		}
	}*/

	int dimension = 2;
	float scale = 40.0f;
	BackgroundTile* tile;
	for (int y = -dimension/2; y < dimension/2+1; y++) {
		for (int x = -dimension/2; x < dimension/2+1; x++) {
			//std::cout << "Placing tile at (" << (float)x << ',' << (float)y << ")\n";
			tile = new BackgroundTile();
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::scale(model, glm::vec3(scale));
			tile->setModel(glm::translate(model, glm::vec3((float)x, (float)y, 0.0f)));
			tiles.push_back(tile);
		}
	}
}

Background::~Background() {
	for (BackgroundTile* tile : tiles)
		delete(tile);
}

std::vector<BackgroundTile*> Background::getTiles() {
	return tiles;
}

std::vector<glm::mat4> Background::getModels() {
	return models;
}

void Background::draw(glm::mat4 view, glm::mat4 projection) {
	for (BackgroundTile* tile : tiles)
		tile->draw(view, projection);
}