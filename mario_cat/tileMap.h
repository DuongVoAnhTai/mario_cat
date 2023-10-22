#pragma once
#include "game.h"

#define MAX_TILE 20

class TileMat : public Game
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
private:
	Map game_map;
	TileMat tile_mat[MAX_TILE];
	sf::Texture tileSheet;

public:
	GameMap() { ; }
	~GameMap() { ; }

	void loadMap(char* name);
	void render(sf::RenderTarget& target);
};

