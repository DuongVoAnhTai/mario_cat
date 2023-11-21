#include "global.h"
#include "game.h"

//Private function
void Game::initVariables()
{
	this->window = nullptr;
	this->mark_value = 0;
	this->last_value = 0;
	this->outputFile.open("Diem.txt", ios::app);
	if (!outputFile.is_open())
	{
		cerr << "Không thể mở tệp tin." << endl;
	}
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
}

//Win Screen
void Game::initWinScr() {
	if (!this->WinScrText.loadFromFile("PNG_file/WinScreen.png")) {
		cout << "Win Screen ERROR";
	}
	this->WinScr.setTexture(this->WinScrText);

	this->WinScr.setScale(
		static_cast<float>(this->window->getSize().x) / this->WinScr.getGlobalBounds().width,
		static_cast<float>(this->window->getSize().y) / this->WinScr.getGlobalBounds().height
	);
}

//Map
void Game::initMap()
{
	char name[] = "PNG_file/map.txt";

	//Map ban đầu:
	this->originalMap.loadMap(name);

	//Map hiện tại
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
	if (!buffer1.loadFromFile("./MUSIC_File/nhacnenmario.ogg")) {
		// Error handling
		cout << "error!" << endl;
	}

	if (!testBuffer.loadFromFile("./MUSIC_File/Pswitch.mp3")) {
		cout << "error!" << endl;
	}

	

	sound1.setBuffer(buffer1);
	
}

void Game::initBackgroundMusic() {
	if (!backgroundMusic.openFromFile("./MUSIC_File/nhacnenmario.ogg")) {
		std::cerr << "Error loading background music!" << std::endl;
	}
}

void Game::initGameOverMusic() {
	if (!gameOverMusic.openFromFile("./MUSIC_File/gameover.mp3")) {
		std::cerr << "Error loading game over music!" << std::endl;
	}
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initBackGr();
	this->initWinScr();
	this->initMap();
	this->initPlayer();
	this->initEnemies();
	this->initMusic();
	this->initBackgroundMusic();
	this->initGameOverMusic();
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

void Game::renderWinScr()
{
	this->window->draw(this->WinScr);
}

void Game::renderMap()
{
	this->map.render(*this->window);
}

void Game::bubbleSort(vector<int>& arr)
{
	int n = arr.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//Player
void Game::updatePlayer()
{
	this->map_data = map.getMap();
	this->player->setMapXY(map_data.start_x, map_data.start_y);
	this->player->update(this->map_data);

	//Khi rớt xuống vực
	if (this->player->getRect().top >= map_data.max_y)
	{
		if (this->player->getAnimStates() != this->player->WIN)
		{
			this->map_data = originalMap.getMap();
			this->map.setMap(map_data);
			player->setRect(0, 0);
			this->updatePlayer();
			player->setComeBackTime(60);
			sf::sleep(sf::seconds(1));
		}
	}
	if (this->player->getAnimStates() == this->player->WIN)
	{
		//Save file and sort file
		this->last_value = this->mark_value;
		this->mark_value = 0;
		outputFile << last_value << endl;
		outputFile.close();
		
		inputFile.open("Diem.txt");
		if (inputFile.is_open())
		{
			int score;
			while (inputFile >> score)
				scores.push_back(score);
			inputFile.close();
			bubbleSort(scores);

			diem.open("Sap_xep.txt");
			if (diem.is_open())
			{
				for (const int& score : scores)
				{
					diem << score << endl;
				}
				diem.close();
			}
		}
		else
		{
			std::cerr << "Không thể mở tệp đầu vào." << endl;
		}
		return;
	}
}

void Game::renderPlayer()
{
	this->player->render(*this->window); //goi ham ve player
}

//Enemies
vector <Enemy*> Game::listEnemy()
{
	vector<Enemy*> list_enemy;
	Enemy* enemy_obj = new Enemy[22];

	for (int i = 0; i < 22; i++)
	{
		Enemy* p_threat = (enemy_obj + i);
		if (p_threat != NULL)
		{
			p_threat->set_type_move(Enemy::MOVE_IN_SPACE);
			p_threat->set_x_pos(700 + i * 930);
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
				if (this->player->getAnimStates() != this->player->WIN)
				{
					this->map_data = originalMap.getMap();
					this->map.setMap(map_data);
					player->setRect(0, 0);
					this->updatePlayer();
					player->setComeBackTime(60);
					sf::sleep(sf::seconds(1));
					continue;
				}
			}
		}
	}
}

void Game::renderEnemies()
{
	this->updateEnemies();
}

//Function
void Game::pollEvent() {

	while (this->window->pollEvent(this->ev)) 
	{
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape) 
		{
			this->window->close();
			outputFile.close();
		}
	}
}

void Game::music()
{
	sound1.play();
	if (backgroundMusic.getStatus() != sf::Music::Playing) {
		backgroundMusic.play();
	}
	
	sound1.play();
	
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

	if (!player->getWin())
	{
		this->renderBackGr();

		this->renderPlayer();
		map.setMap(map_data);
		this->renderMap();

		this->renderEnemies();

	}
	else
	{
		this->renderWinScr();
	}
		//Draw
		this->window->display();

	//Point in game
	this->mark_value += 1;

	
}