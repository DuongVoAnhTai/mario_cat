#pragma once
#include"player.h"

class Game {
private:
	//Variable
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Player
	Player* player;

	//Private function
	void initVariables();
	void initWindow();

	void initPlayer();
public:
	//Constructor
	Game();
	virtual ~Game();

	//Access
	const bool running();

	//Player
	void updatePlayer();
	void renderPlayer();

	//Function
	void pollEvent();
	void update();
	void render();
};