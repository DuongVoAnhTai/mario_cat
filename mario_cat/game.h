#pragma once
#include"global.cpp"

class game {
private:
	//variable
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//private function
	void initVariables();
	void initWindow();
public:
	//Constructor
	game();
	virtual ~game();

	//access
	const bool running();

	//function
	void pollEvent();
	void update();
	void render();
};