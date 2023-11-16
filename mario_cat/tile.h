#pragma once

class TileMat
{
private:
	//Print image
	sf::Sprite sprite;
	sf::Texture texture;
	
public:
	TileMat();
	~TileMat();

	void loadIMG(string path);
	void setRect(int rect_x, int rect_y);

	//Render
	void update();
	void render(sf::RenderTarget& target);
};

