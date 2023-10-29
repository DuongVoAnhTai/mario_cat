#pragma once
#include "tile.h"

#define GRAVITY 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8

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
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	bool on_ground;

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
	sf::Vector2f position();

	void updateAnimation();
	void updateMovement(Map& map_data);
	void doPlayer();
	void collisionMap(Map& map_data);

	void update(Map& map_data);
	void render(sf::RenderTarget& target); //ve 1 anh len man hinh
};