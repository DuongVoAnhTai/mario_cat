#include "global.h"
#include "enemy.h"

//Core
void Enemy::initVariables()
{
	this->speed = -1.f;
}

void Enemy::initTexture() {
	if (!this->textureSheet.loadFromFile("PNG_file/Mushroom.png"))
	{
		std::cout << "ERROR LOAD IMGE";
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->frame = sf::IntRect(0, 0, 1024, 800);
	this->sprite.setTextureRect(this->frame);
	this->sprite.setScale(0.1f, 0.1f);
}

void Enemy::initAnimation()
{

}


Enemy::Enemy(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Enemy::~Enemy()
{

}

//Function
void Enemy::update()
{
	this->sprite.move(this->speed, 0.f);
}

void Enemy::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
}
