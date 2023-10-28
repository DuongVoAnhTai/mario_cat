#pragma once
#include"player.h"
#include"enemy.h"
#include"tileMap.h"

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
	Player* player;

	//Enemies
	Enemy* enemy;

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
	void updatetEnemies();
	void renderEnemies();


	//Function
	void pollEvent();
	void update();
	void render();
};