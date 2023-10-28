#pragma once

class TileMat
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	//sf::IntRect rect;
	
	/*unsigned int rect_w;
	unsigned int rect_h;*/

public:
	TileMat();
	//TileMat(sf::Texture* texture_sheet, sf::IntRect texture_rect);
	~TileMat();

	//const sf::FloatRect getGlobalBound();

	void loadIMG(string path);
	void setRect(int rect_x, int rect_y);
	//void getRect();

	void update();
	void render(sf::RenderTarget& target);
};

