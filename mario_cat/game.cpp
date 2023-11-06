#include "global.h"
#include "game.h"

//Private function
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode::getFullscreenModes()[0];
	this->window = new sf::RenderWindow(this->videoMode, "Cat_mario", sf::Style::Fullscreen);
	this->window->setFramerateLimit(60); //gioi han khung hinh thanh 144
}

//BackGr
void Game::initBackGr() {
	if (!this->BackGrText.loadFromFile("PNG_file/Background.jpg")) {
		cout << "Back Ground ERROR";
	}
	this->BackGr.setTexture(this->BackGrText);

	this->BackGr.setScale(
		static_cast<float>(this->window->getSize().x) / this->BackGr.getGlobalBounds().width,
		static_cast<float>(this->window->getSize().y) / this->BackGr.getGlobalBounds().height
	);
	//cout << this->window->getSize().y;
}

//Map
void Game::initMap()
{
	char name[] = "PNG_file/map.txt";
	this->map.loadMap(name);
	this->map.update();
	this->map_data = map.getMap();
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies() {
	this->enemy_list = listEnemy();
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initMap();
	this->initPlayer();
	this->initEnemies();
	this->initBackGr();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->enemy;
}

const bool Game::running()
{
	return this->window->isOpen();
}

void Game::renderBackGr() 
{
	this->window->draw(this->BackGr);
}

void Game::renderMap()
{
	this->map.render(*this->window);
}

//Player
void Game::updatePlayer()
{
	this->player->update(this->map_data);
}

void Game::renderPlayer()
{
	this->player->render(*this->window); //goi ham ve player
}

//Enemies
vector <Enemy*> Game::listEnemy()
{
	vector<Enemy*> list_enemy;
	Enemy* enemy_obj = new Enemy[20];

	for (int i = 0; i < 20; i++)
	{
		Enemy* p_threat = (enemy_obj + i);
		if (p_threat != NULL)
		{
			p_threat->set_x_pos(700 + i * 1200);
			p_threat->set_y_pos(250);

			list_enemy.push_back(p_threat);
		}
	}
	return list_enemy;
}


void Game::updateEnemies()
{
	//this->enemy->update();
	for (int i = 0; i < enemy_list.size(); i++)
	{
		Enemy* p_enemy = enemy_list.at(i);
		if (p_enemy != NULL)
		{
			p_enemy->setMapXY(map_data.start_x, map_data.start_y);
			p_enemy->doPlayer(map_data);
			p_enemy->render(*this->window);
		}
	}
}

void Game::renderEnemies()
{
	//this->enemy->render(*this->window);
}

//Function
void Game::pollEvent() {

	while (this->window->pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::update()
{
	this->pollEvent();
	this->updatePlayer();
}

void Game::render()
{
	/* quy tac ve hinh anh len man hinh
		- xoa man hinh
		- tao doi tuong
		- ve len man hinh
	*/

	this->window->clear();

	//Render game
	//Vẽ background nhiều lần để lặp lại nó trên cửa sổ đồ họa
	/*for (int x = 0; x < this->window->getSize().x; x += BackGrText.getSize().x) {
		for (int y = 0; y < this->window->getSize().y; y += BackGrText.getSize().y) {
			BackGr.setPosition(x, 0);
			this->renderBackGr();
	//this->renderBackGr();
	this->renderMap();
	}*/
	this->renderBackGr();
	this->renderMap();
	//cout << position.x;
	this->renderPlayer();
	this->updateEnemies();

	//this->renderEnemies();

	//Draw
	this->window->display();
}