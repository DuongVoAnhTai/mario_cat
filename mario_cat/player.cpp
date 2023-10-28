#include "global.h"
#include"player.h"

void Player::initVariables()
{

	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture()
{

	if (!this->textureSheet.loadFromFile("PNG_file/Cat.png"))
	{
		std::cout << "ERROR LOAD IMAGE";
	}
}

void Player::initAnimation()
{
	this->animationTimer.restart();
}

void Player::initSprite()
{

	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 35.5f, 48.f);
	this->sprite.setTextureRect(this->currentFrame); //lay frame thu 1 cua hinh anh
	this->sprite.setScale(sf::Vector2f(1.f, 1.f)); //set lai ti le cua hinh anh
}

Player::Player(float pos_x, float pos_y)
{

	this->sprite.setPosition(pos_x, pos_y);
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
}

Player::~Player()
{

}

sf::Vector2f Player::position()
{
	return this->sprite.getPosition();
}

void Player::updateMovement()
{

	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->sprite.move(-2.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}

	//Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->sprite.move(2.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
}

void Player::updateAnimation()
{

	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		//thoi gian troi qua 0.5s thi reset frame
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5)
		{
			this->currentFrame.top = 0.f;
			cout << this->currentFrame.left << " ";

			this->currentFrame.left += 35.5f;
			if (this->currentFrame.left >= 70.f)
			{
				cout << this->currentFrame.left << " ";
				this->currentFrame.left = 0.f;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		//thoi gian troi qua 0.5s thi reset frame
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 35.5f;
			if (this->currentFrame.left >= 70.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setOrigin(0.f, 0.f);
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		//thoi gian troi qua 0.5s thi reset frame
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 35.5f;
			if (this->currentFrame.left >= 70.f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-1.f, 1.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.f, 0.f);
	}
}

void Player::update()
{

	this->updateMovement();
	this->updateAnimation();
}

void Player::render(sf::RenderTarget& target)
{

	target.draw(this->sprite); //ve len man hinh

	/*sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(2.f);
	circ.setPosition(this->sprite.getPosition());

	target.draw(circ);*/
}
