#pragma once

enum PLAYER_ANIMATION_STATES {
	IDLE = 0, //trang thai player khong tuong tac
	MOVING_LEFT,
	MOVING_RIGHT,
	JUMPING,
	DIE
};

class Player {
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

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
	Player(float x, float y);
	virtual ~Player();

	//Function
	sf::Vector2f position();
	void updateAnimation();
	void updateMovement();
	void update();
	void render(sf::RenderTarget& target); //ve 1 anh len man hinh
};