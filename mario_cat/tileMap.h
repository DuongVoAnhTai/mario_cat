#pragma once
#include "tile.h"

#define MAX_TILE 20

class GameMap
{
private:
	Map game_map;
	TileMat tile_mat[MAX_TILE];
	sf::Texture* tileSheet;
	sf::VideoMode size;

public:
	GameMap();
	~GameMap();

	void loadMap(char* name);
	Map getMap() const { return game_map; }

	void update();
	void render(sf::RenderTarget& target);
};

