#pragma once
#include "tile.h"

#define MAX_TILE 30

class GameMap
{
private:
	//Variables
	Map game_map;
	TileMat tile_mat[MAX_TILE];
	sf::Texture* tileSheet;
	sf::VideoMode size;

public:
	GameMap();
	~GameMap();

	//Coliison map
	void loadMap(char* name);
	Map getMap() const { return game_map; }
	void setMap(Map& map_data) { game_map = map_data; }

	//Render
	void update();
	void render(sf::RenderTarget& target);
};

