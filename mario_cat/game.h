#pragma once
#include"player.h"
#include"enemy.h"
#include"tileMap.h"
#include<vector>

class Game
{
private:
	//Variable
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::SoundBuffer buffer;
	sf::Sound sound;

	//BackGr
	sf::Sprite BackGr;
	sf::Texture BackGrText;

	//Map
	GameMap map;

	//Player
	Map map_data;
	Player* player;

	//Point
	int mark_value;
	int last_value;
	vector<int> scores;
	ofstream outputFile;
	ofstream diem;
	ifstream inputFile;

	//Enemies
	vector<Enemy*> enemy_list;

	//Private function
	void initVariables();
	void initWindow();
	void initBackGr();
	void initMap();
	void initPlayer();
	void initEnemies();
	void initMusic();

public:
	//Constructor
	Game();
	virtual ~Game();

	//Access
	const bool running();

	//Background
	void renderBackGr();

	//Map
	void renderMap();

	//Sort
	void bubbleSort(vector<int>& arr);

	//Player
	void updatePlayer();
	void renderPlayer();

	//Enemies
	vector<Enemy*> listEnemy();
	void updateEnemies();
	void renderEnemies();

	//Function
	void pollEvent();
	void music();
	void update();
	void render();
};