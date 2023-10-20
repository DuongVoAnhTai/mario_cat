#pragma once

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	sf::IntRect frame;

	float speed;

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Function
	void update();
	void render(sf::RenderTarget& target);
};