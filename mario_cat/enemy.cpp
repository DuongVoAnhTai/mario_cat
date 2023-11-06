#include "global.h"
#include "enemy.h"

//Core
void Enemy::initVariables()
{
	/*width_frame = 0;
	height_frame = 0;*/
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	on_ground = 0;
	come_back_time = 0;
}

void Enemy::initTexture() 
{
	if (!this->textureSheet.loadFromFile("PNG_file/Mushroom.png"))
	{
		std::cout << "ERROR LOAD IMGE";
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->frame = sf::IntRect(0, 0, 61, 47);
	this->sprite.setTextureRect(this->frame);
	this->sprite.setScale(1.f, 1.f);
}

void Enemy::initAnimation()
{

}

Enemy::Enemy()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Enemy::~Enemy()
{

}

//Function
void Enemy::doPlayer(Map& gmap)
{
	if (come_back_time == 0)
	{
		x_val = 0;
		y_val += ENEMY_GRAVITY;

		if (y_val >= ENEMY_MAX_FALL_SPEED)
		{
			y_val = ENEMY_MAX_FALL_SPEED;
		}

		collisionMap(gmap);
	}
	else if (come_back_time > 0)
	{
		come_back_time--;
		if (come_back_time == 0)
		{
			x_val = 0;
			y_val = 0;
			if (x_pos > 256)
			{
				x_pos -= 256;
			}
			else
			{
				x_pos = 0;
			}
			y_pos = 0;
			come_back_time = 0;
		}
	}
}

void Enemy::collisionMap(Map& gmap)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check horizontal (chieu ngang)
	int height_min = this->frame.height < TILE_SIZE ? this->frame.height : TILE_SIZE;

	//O thu bao nhieu
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + this->frame.width - 1) / TILE_SIZE;

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
			if (gmap.tile[y1][x2] != 0 || gmap.tile[y2][x2] != 0) //Neu o do ko phai so 0
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= this->frame.width + 1;
				x_val = 0;
			}
		}
		else if (x_val < 0) //Moving left
		{
			if (gmap.tile[y1][x1] != 0 || gmap.tile[y2][x1] != 0)
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	}

	//Check vertical (chieu cao)
	int width_min = this->frame.width < TILE_SIZE ? this->frame.width : TILE_SIZE;
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + this->frame.height - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_X && y1 >= 0 && y2 < MAX_Y)
	{
		if (y_val > 0)
		{
			if (gmap.tile[y2][x1] != 0 || gmap.tile[y2][x2] != 0)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= this->frame.height + 1;
				y_val = 0;
				on_ground = true;
			}
		}
		else if (y_val < 0)
		{
			if (gmap.tile[y1][x1] != 0 || gmap.tile[y1][x2] != 0)
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
	else if (x_pos + this->frame.width > gmap.max_x)
	{
		x_pos = gmap.max_x - this->frame.width - 1;
	}

	if (y_pos > gmap.max_y)
	{
		come_back_time = 60;
	}
}

void Enemy::update()
{
	//this->sprite.move(this->speed, 0.f);
}

void Enemy::render(sf::RenderTarget& target)
{
	this->sprite.setPosition(x_pos, y_pos);
	target.draw(this->sprite);
}
