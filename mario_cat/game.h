#pragma once
#include"player.h"
#include"enemy.h"
#include"tileMap.h"
#include<vector>

class Game
{
private:
	//Variable
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//BackGr
	sf::Sprite BackGr;
	sf::Texture BackGrText;

	//Map
	GameMap map;

	//Player
	Map map_data;
	Player* player;

	//Enemies
	Enemy* enemy;
	vector<Enemy*> enemy_list;

	//Private function
	void initVariables();
	void initWindow();
	void initBackGr();
	void initMap();
	void initPlayer();
	void initEnemies();

public:
	//Constructor
	Game();
	virtual ~Game();

	//Access
	const bool running();

	//Background
	void renderBackGr();

	//Map
	void renderMap();

	//Player
	void updatePlayer();
	void renderPlayer();

	//Enemies
	vector<Enemy*> listEnemy();
	void updateEnemies();
	void renderEnemies();

	//Function
	void pollEvent();
	void update();
	void render();
};