#include "game.h"


void game::initVariables() {
	this->window = nullptr;	
}

void game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Cat_mario", sf::Style::Close);
}

game::game() {
	this->initVariables();
	this->initWindow();
}

game::~game() {
	delete this->window;
}

const bool game::running() {
	return this->window->isOpen();
}

void game::pollEvent() {
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void game::update() {
	this->pollEvent();
}

void game::render() {

	/*
		- xoa cua so
		- tao doi tong
		- ve len man hinh
	*/

	this->window->clear(sf::Color::Blue);

	//draw
	this->window->display();
}