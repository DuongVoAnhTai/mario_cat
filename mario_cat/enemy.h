#pragma once

#define ENEMY_GRAVITY 0.8
#define ENEMY_MAX_FALL_SPEED 10
#define SPEED_ENEMY 3

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	sf::IntRect frame;

	bool on_ground;
	int come_back_time;
	/*int width_frame;
	int height_frame;*/
	float x_pos;
	float y_pos;
	float x_val;
	float y_val;
	int map_x;
	int map_y;

	int type_move;
	int animationA;
	int animationB;
	Input input_type;

	//Core
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();

public:
	Enemy();
	virtual ~Enemy();

	enum TyoeMove
	{
		MOVE_IN_SPACE = 1
	};

	//Function
	/*int get_width_frame() { return width_frame; }
	int get_height_frame() { return height_frame; }*/

	void set_x_val(const float& xVal) { x_val = xVal; }
	void set_y_val(const float& yVal) { y_val = yVal; }

	void set_x_pos(const float& xp) { x_pos = xp; }
	void set_y_pos(const float& yp) { y_pos = yp; }
	float get_x_pos() const { return x_pos; }
	float get_y_pos() const { return y_pos; }

	void setMapXY(const int& mp_x, const int& mp_y) { map_x = mp_x; map_y = mp_y; }

	void doPlayer(Map& gmap);	
	void collisionMap(Map& gmap);

	void set_type_move(const int& typeMove) { type_move = typeMove; }
	void setAnimation(const int& pos_a, const int& pos_b) { animationA = pos_a; animationB = pos_b; }
	void set_input_left(const int& ipLeft) { input_type.left = ipLeft; }
	void impMoveType(sf::RenderTarget& target);
	//void impMoveType

	void update();
	void render(sf::RenderTarget& target);
};