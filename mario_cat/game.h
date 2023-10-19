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

	//BackGr
	sf::Sprite BackGr;
	sf::Texture BackGrText;
	//Private function
	void initVariables();
	void initWindow();
	void initBackGr();
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
	void followPlayer();
	void renderBackGr();
	void pollEvent();
	void update();
	void render();
};