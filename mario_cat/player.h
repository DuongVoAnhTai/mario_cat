#pragma once
#include "tile.h"

#define GRAVITY 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 6

enum PLAYER_ANIMATION_STATES
{
	IDLE = 0, //trang thai player khong tuong tac
	MOVING_LEFT,
	MOVING_RIGHT,
	JUMPING,
	DIE
};

class Player
{
private:
	//Print image
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::VideoMode size;

	//Variables
	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	int come_back_time;

	bool on_ground;

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

public:
	Player(/*float pos_x, float pos_y*/);
	virtual ~Player();

	//Function
	void updateAnimation();
	void updateMovement(Map& map_data);

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
};