#include "global.h"
#include "game.h"

//Private function
void Game::initVariables() {

	this->window = nullptr;
}

void Game::initWindow() {

	this->videoMode = sf::VideoMode::getFullscreenModes()[0];
	this->window = new sf::RenderWindow(this->videoMode, "Cat_mario", sf::Style::Fullscreen);
	this->window->setFramerateLimit(144); //gioi han khung hinh thanh 144
}

void Game::initPlayer() {

	this->player = new Player();
}

Game::Game() {

	this->initVariables();
	this->initWindow();
	this->initPlayer();
}

Game::~Game() {

	delete this->window;
	delete this->player;
}

const bool Game::running() {

	return this->window->isOpen();
}

//Player
void Game::updatePlayer() {

	this->player->update();
}

void Game::renderPlayer() {

	this->player->render(*this->window); //goi ham ve player
}

//Function
void Game::pollEvent() {

	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::update() {

	this->pollEvent();
	this->updatePlayer();
}

void Game::render() {

	/* quy tac ve hinh anh len man hinh
		- xoa man hinh
		- tao doi tuong
		- ve len man hinh
	*/

	this->window->clear();

	//Render game
	this->renderPlayer();

	//Draw
	this->window->display();
}