#pragma once
#include "tile.h"

#define GRAVITY 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 6

#define TP_BLOCK 8
#define LUCKY_BLOCK 7
#define CHECK_POINT 12
#define INVISIBLE_BLOCK 14
#define INVISIBLE_JUMP_UP 15
#define JUMP_UP 16
#define WALL 17

#define range 12

class Player
{
private:
	//Print image
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::VideoMode size;
	sf::SoundBuffer buffer2;
	sf::SoundBuffer buffer3;
	sf::SoundBuffer buffer4;
	sf::Sound sound2;
	sf::Sound sound3;
	sf::Sound sound4;

	//Variables
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int come_back_time;

	bool on_ground;
	bool win;

	int mapX;
	int mapY;

	//Animation
	short animState;
	sf::IntRect currentFrame;

	//Movement

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initMusic();

public:

enum PLAYER_ANIMATION_STATES
{
	IDLE = 0, //trang thai player khong tuong tac
	MOVING_LEFT,
	MOVING_RIGHT,
	JUMPING,
	WIN
};

	Player(/*float pos_x, float pos_y*/);
	virtual ~Player();

	//Function
	void updateAnimation();
	void updateMovement(Map& map_data);
	short getAnimStates() { return this->animState; }
	short getWin() { return win; }

	//Collision Map
	void collisionMap(Map& map_data);
	void setMapXY(const int& map_x, const int& map_y) { mapX = map_x; mapY = map_y; }
	void centerEntityOnMap(Map& map_data);
	void setComeBackTime(const int& cbTime) { come_back_time = cbTime; }
	void setRect(const int& xPos, const int& yPos) { x_pos = xPos; y_pos = yPos; };

	//Give bound to check collision
	sf::FloatRect getRect();

	//Render
	void update(Map& map_data);
	void render(sf::RenderTarget& target); //ve 1 anh len man hinh

	void handleInput(char key);
};