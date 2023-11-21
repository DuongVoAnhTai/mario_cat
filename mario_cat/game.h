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
	sf::SoundBuffer buffer1;
	sf::SoundBuffer buffer2;
	sf::SoundBuffer buffer3;
	sf::SoundBuffer buffer4;
	sf::Sound sound1;
	sf::Sound sound2;
	sf::Sound sound3;
	sf::Sound sound4;
	sf::SoundBuffer testBuffer;
	sf::Sound testSound;
	sf::Music backgroundMusic;
	sf::Music gameOverMusic;

	//BackGr
	sf::Sprite BackGr;
	sf::Texture BackGrText;

	//Win Screen
	sf::Sprite WinScr;
	sf::Texture WinScrText;

	//Map
	GameMap map;
	GameMap originalMap;

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
	void initWinScr();
	void initMap();
	void initPlayer();
	void initEnemies();
	void initMusic();
	void initBackgroundMusic();
	void initGameOverMusic();
    
public:
	//Constructor
	Game();
	virtual ~Game();

	//Access
	const bool running();

	//Background
	void renderBackGr();

	//Win Screen
	void renderWinScr();

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