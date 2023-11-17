#include "global.h"
#include"player.h"
#include "game.h"
#include <cstdlib>

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	x_val = 0;
	y_val = 0;

	x_pos = 0;
	y_pos = 0;

	heart = 3;

	come_back_time = 0;

	on_ground = false;

	mapX = 0;
	mapY = 0;

	//this->bound = sprite.getGlobalBounds();

	this->size = sf::VideoMode::getDesktopMode();
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
	this->currentFrame = sf::IntRect(0, 0, 35.5f, 47.f);
	this->sprite.setTextureRect(this->currentFrame); //lay frame thu 1 cua hinh anh
	this->sprite.setScale(sf::Vector2f(1.f, 1.f)); //set lai ti le cua hinh anh
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
}

Player::~Player()
{

}

void Player::updateMovement(Map& map_data)
{
	if (come_back_time == 0) {

		this->animState = PLAYER_ANIMATION_STATES::IDLE;
		x_val = 0;
		y_val += 0.8;
		//this->sprite.move(0.f, y_val);

		if (y_val >= MAX_FALL_SPEED)
		{
			y_val = MAX_FALL_SPEED;
		}

		//Left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			x_val -= PLAYER_SPEED;
			this->sprite.move(x_val, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
		}

		//Right
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			x_val += PLAYER_SPEED;
			this->sprite.move(x_val, 0.f);
			this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		}

		//Jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			if (on_ground == true)
			{
				y_val = -25;
				this->sprite.move(0, y_val);
				on_ground = false;

			}
			this->sprite.move(x_val, 0);
			this->animState = PLAYER_ANIMATION_STATES::JUMPING;
		}
		collisionMap(map_data);
		centerEntityOnMap(map_data);
	}
	if (come_back_time > 0) {
		come_back_time--;
		if (come_back_time == 0) {
			x_pos = 0;
			y_pos = 0;
			x_val = 0;
			y_val = 0;
		}
	}
}

void Player::centerEntityOnMap(Map& map_data)
{
	int MAX_WIDTH = size.width;
	int MAX_HEIGHT = size.height;
	map_data.start_x = x_pos - (MAX_WIDTH / 2.0);
	if (map_data.start_x < 0)
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + MAX_WIDTH >= map_data.max_x)
	{
		map_data.start_x = map_data.max_x - MAX_WIDTH;
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
			//cout << this->currentFrame.left << " ";

			this->currentFrame.left += 35.5f;
			if (this->currentFrame.left >= 70.f)
			{
				//cout << this->currentFrame.left << " ";
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
			if (on_ground == true)
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
			else
			{
				this->currentFrame.top = 96;
				this->currentFrame.left = 0.f;
				this->sprite.setTextureRect(this->currentFrame);
			}
		}
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setOrigin(0.f, 0.f);
	}

	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		//thoi gian troi qua 0.5s thi reset frame
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.5)
		{
			if (on_ground == true)
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
			else
			{
				this->currentFrame.top = 96;
				this->currentFrame.left = 0.f;
				this->sprite.setTextureRect(this->currentFrame);
			}
		}
		this->sprite.setScale(-1.f, 1.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 1.f, 0.f);
	}
}

void Player::collisionMap(Map& map_data)
{
	int x1 = 0;
 	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	// Sinh số ngẫu nhiên trong khoảng 1 đến range
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int random_Value = std::rand() % range + 1;

	//Check horizontal (chieu ngang)
	int height_min = this->currentFrame.height < TILE_SIZE ? this->currentFrame.height : TILE_SIZE;

	//O thu bao nhieu
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + this->currentFrame.width - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if ((x1 >= 0 && x2 < MAX_X) && (y1 >= 0 && y2 < MAX_Y))
	{
		if (x_val > 0) //Moving right
		{
			/*
				x1y1---------x2y1
				|				|
				|				|
				x1y2---------x2y2
			*/
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			//Đưa người chơi về đầu map khi va chạm vào block TP và check point
			if (val1 == TP_BLOCK || val2 == TP_BLOCK || val1 == CHECK_POINT || val2 == CHECK_POINT)
			{
				x_pos = 0;
				y_pos = 0;
			}
			
			else
			{
				if (val1 != 0 || val2 != 0) //Neu o do ko phai so 0
				{
					x_pos = x2 * TILE_SIZE;
					x_pos -= this->currentFrame.width + 1;
					x_val = 0;
				}
			}
			
		}
		else if(x_val < 0) //Moving left
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 == TP_BLOCK || val2 == TP_BLOCK || val1 == CHECK_POINT || val2 == CHECK_POINT)
			{
				x_pos = 0;
				y_pos = 0;
			}
			
			else
			{
				if (val1 != 0 || val2 != 0)
				{
					x_pos = (x1 + 1) * TILE_SIZE;
					x_val = 0;
				}
			}
			
		}
	}

	//Check vertical (chieu cao)
	int width_min = this->currentFrame.width < TILE_SIZE ? this->currentFrame.width : TILE_SIZE;
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + this->currentFrame.height - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_X && y1 >= 0 && y2 < MAX_Y)
	{
		if (y_val > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == TP_BLOCK || val2 == TP_BLOCK || val1 == CHECK_POINT || val2 == CHECK_POINT)
			{
				x_pos = 0;
				y_pos = 0;
			}
			
			else
			{
				if (val1 != 0 || val2 != 0)
				{
					y_pos = y2 * TILE_SIZE;
					y_pos -= this->currentFrame.height + 1;
					y_val = 0;
					on_ground = true;
				}
			}
			
		}
		else if(y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if (val1 == TP_BLOCK || val2 == TP_BLOCK || val1 == CHECK_POINT || val2 == CHECK_POINT)
			{
				x_pos = 0;
				y_pos = 0;
			}
			else if (val1 == LUCKY_BLOCK || val2 == LUCKY_BLOCK)
			{
				//LUCKY BLOCK va chạm khi ngươi chơi nhảy lên:

				if (random_Value >= 1 && random_Value <= 3)
				{
					for (int i = 0; i < 3; i++)
					{
						map_data.tile[y1][x1 - i] = 1;
						map_data.tile[y1][x2 - i] = 1;
					}
					for (int i = 0; i < 3; i++)
					{
						map_data.tile[y1][x1 + i] = 1;
						map_data.tile[y1][x2 + i] = 1;
					}
				}

				if (random_Value >= 4 && random_Value <= 6)
				{
					for (int i = 0; i < 3; i++)
					{
						map_data.tile[y1][x1 - i] = 7;
						map_data.tile[y1][x2 - i] = 7;
					}
					for (int i = 0; i < 3; i++)
					{
						map_data.tile[y1][x1 + i] = 7;
						map_data.tile[y1][x2 + i] = 7;
					}
				}

				if (random_Value >= 7 && random_Value <= 9)
				{
					for (int i = 0; i <= 4; i++)
					{
						map_data.tile[20 - i][x1] = 0;
						map_data.tile[20 - i][x2] = 0;
						map_data.tile[20 - i][x1 - 1] = 0;
						map_data.tile[20 - i][x2 - 1] = 0;
						map_data.tile[20 - i][x1 - 2] = 0;
						map_data.tile[20 - i][x2 - 2] = 0;
						map_data.tile[20 - i][x1 - 3] = 0;
						map_data.tile[20 - i][x2 - 3] = 0;
					}
					for (int i = 0; i <= 4; i++)
					{
						map_data.tile[20 - i][x1] = 0;
						map_data.tile[20 - i][x2] = 0;
						map_data.tile[20 - i][x1 + 1] = 0;
						map_data.tile[20 - i][x2 + 1] = 0;
						map_data.tile[20 - i][x1 + 2] = 0;
						map_data.tile[20 - i][x2 + 2] = 0;
						map_data.tile[20 - i][x1 + 3] = 0;
						map_data.tile[20 - i][x2 + 3] = 0;
					}
				}

				if (random_Value >= 10 && random_Value <= 12)
				{
					x_pos = 0;
					y_pos = 0;
				}
			}

			if (val1 != 0 || val2 != 0)
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}
	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0)
	{
		x_pos = 0;
	}
	else if (x_pos + this->currentFrame.width > map_data.max_x)
	{
		x_pos = map_data.max_x - this->currentFrame.width - 1;
	}

	//if (y_pos > map_data.max_y) {}
}

sf::FloatRect Player::getRect()
{
	sf::FloatRect bound;
	bound = sprite.getGlobalBounds();
	return bound;
}

void Player::update(Map& map_data)
{
	this->sprite.setPosition(x_pos - mapX, y_pos - mapY);
	this->updateMovement(map_data);
	this->updateAnimation();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite); //ve len man hinh
}
