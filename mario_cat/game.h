#pragma once
#include"player.h"
#include"enemy.h"

class Game
{
private:
	//Variable
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Player
	Player* player;

	//BackGr
	sf::Sprite BackGr;
	sf::Texture BackGrText;
	//Enemies
	Enemy* enemy;

	//Private function
	void initVariables();
	void initWindow();
	void initBackGr();
	void initPlayer();
	void initEnemies();
public:
	//Constructor
	Game();
	virtual ~Game();

	//Access
	const bool running();

	//Player
	void updatePlayer();
	void renderPlayer();

	//Enemies
	void updatetEnemies();
	void renderEnemies();

	//Background
	void renderBackGr();

	//Function
	void pollEvent();
	void update();
	void render();
};