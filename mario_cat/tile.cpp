#include "global.h"
#include "Tile.h"

TileMat::TileMat()
{
	//this->texture = nullptr;
	/*this->rect.left = 0;
	this->rect.top = 0;*/
}


//TileMat::TileMat(sf::Texture* texture_sheet, sf::IntRect texture_rect)
//{
//	this->sprite.setTexture(*texture_sheet);
//	this->sprite.setTextureRect(texture_rect);
//}

TileMat::~TileMat()
{
	//delete this->texture;
}

//const sf::FloatRect TileMat::getGlobalBound()
//{
//	return this->sprite.getGlobalBounds();
//}

void TileMat::loadIMG(string path)
{
	if (!this->texture.loadFromFile(path.c_str()))
	{
		std::cout << "ERROR LOAD IMAGE";
	}

	else
	{
		this->sprite.setTexture(this->texture);
		/*sf::Vector2u imageSize = this->texture->getSize();
		this->rect_w = imageSize.x;
		this->rect_h = imageSize.y;*/
		
	}
}

void TileMat::setRect(int rect_x, int rect_y)
{
	this->sprite.setPosition(rect_x, rect_y);
}

void TileMat::update()
{
}

void TileMat::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}