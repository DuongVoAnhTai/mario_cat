#include "global.h"
#include "game.h"

//Private function
void Game::initVariables()
{
	this->window = nullptr;
	this->num_die = 0;
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
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies() {
	this->enemy_list = listEnemy();
}

void Game::initMusic() {
	if (!buffer.loadFromFile("./MUSIC_File/nhacnenmario.ogg")) {
		// Error handling
		cout << "error!" << endl;
	}

	sound.setBuffer(buffer);
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initBackGr();
	this->initMap();
	this->initPlayer();
	this->initEnemies();
	this->initMusic();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	for (int i = 0; i < enemy_list.size(); i++)
	{
		Enemy* p_threat = enemy_list.at(i);
		if (p_threat)
		{
			p_threat = NULL;
		}
	}

	enemy_list.clear();
	//delete this->enemy;
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
	this->map_data = map.getMap();
	this->player->setMapXY(map_data.start_x, map_data.start_y);
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
			p_threat->set_type_move(Enemy::MOVE_IN_SPACE);
			p_threat->set_x_pos(700 + i * 1200);
			p_threat->set_y_pos(250);

			int pos1 = p_threat->get_x_pos() - 120;
			int pos2 = p_threat->get_x_pos() + 120;
			p_threat->set_input_left(1);
			p_threat->setAnimation(pos1, pos2);

			list_enemy.push_back(p_threat);
		}
	}
	return list_enemy;
}


void Game::updateEnemies()
{
	
	for (int i = 0; i < enemy_list.size(); i++)
	{
		Enemy* p_enemy = enemy_list.at(i);
		//p_enemy->update();
		if (p_enemy != NULL)
		{
			p_enemy->setMapXY(map_data.start_x, map_data.start_y);
			p_enemy->impMoveType(*this->window);
			p_enemy->doPlayer(map_data);
			p_enemy->render(*this->window);

			sf::FloatRect rect_player = player->getRect();
			sf::FloatRect rect_enemy = p_enemy->getRect();
			bool coll = globalFunc::CheckCollision(rect_player, rect_enemy);
			if (coll)
			{
				num_die++;
				cout << num_die << " ";
				if (num_die <= 2)
				{
					player->setRect(0, 0);
					this->updatePlayer();
					player->setComeBackTime(60);
					sf::sleep(sf::seconds(1));
					continue;
				}
				else
				{
					cout << "Die";
					this->window->close();
					return;

				}
			}
		}
	}
}

void Game::renderEnemies()
{
	this->updateEnemies();

	//this->enemy->render(*this->window);
}

//Function
void Game::pollEvent() {

	while (this->window->pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) 
		{
			this->window->close();
		}
	}
}

void Game::music()
{
	sound.play();
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

	this->renderBackGr();
	
	this->renderPlayer();
	map.setMap(map_data);
	this->renderMap();

	this->renderEnemies();

	//Draw
	this->window->display();

}