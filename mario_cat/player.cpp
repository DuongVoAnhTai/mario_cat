#include "global.h"
#include"player.h"

void Player::initVariables() {

	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture() {

	if (!this->textureSheet.loadFromFile("PNG_file/Cat.png")) {
		std::cout << "ERROR LOAD IMAGE";
	}
}

void Player::initAnimation() {
	
}

void Player::initSprite() {

	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 768, 1056);
	this->sprite.setTextureRect(this->currentFrame); //lay frame thu 1 cua hinh anh
	this->sprite.setScale(sf::Vector2f(0.05f,0.05f)); //set lai ti le cua hinh anh
}

Player::Player(float x, float y) {
	this->sprite.setPosition(x, y);
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
}

Player::~Player()
{

}

sf::Vector2f Player::position() {
	return this->sprite.getPosition();
}

void Player::updateMovement() {
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->sprite.move(-4.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}

	//Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		this->sprite.move(4.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
}

void Player::updateAnimation() {

	if (this->animState == PLAYER_ANIMATION_STATES::IDLE) {
		this->currentFrame.top = 0.f;
		this->currentFrame.left = 0.f;
		this->sprite.setTextureRect(this->currentFrame);
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
		this->currentFrame.top = 0.f;
		this->currentFrame.left = 768.f;
		this->sprite.setTextureRect(this->currentFrame);
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::IDLE) {
		this->currentFrame.top = 1056;
		this->currentFrame.left = 0.f;
		this->sprite.setTextureRect(this->currentFrame);
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT) {
		this->currentFrame.top = 1056;
		this->currentFrame.left = 768.f;
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Player::update() {

	this->updateMovement();
	this->updateAnimation();
}

void Player::render(sf::RenderTarget& target) {

	target.draw(this->sprite); //ve len man hinh
}
