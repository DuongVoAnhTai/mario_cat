#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

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