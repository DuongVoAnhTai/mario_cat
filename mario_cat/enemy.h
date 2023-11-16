#pragma once

#define ENEMY_GRAVITY 0.8
#define ENEMY_MAX_FALL_SPEED 10
#define SPEED_ENEMY 3

class Enemy
{
private:
	//Print image
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::IntRect frame;

	//Variables
	bool on_ground;
	int come_back_time;
	float x_pos;
	float y_pos;
	float x_val;
	float y_val;
	int map_x;
	int map_y;

	//Move
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
	void set_x_val(const float& xVal) { x_val = xVal; }
	void set_y_val(const float& yVal) { y_val = yVal; }

	void set_x_pos(const float& xp) { x_pos = xp; }
	void set_y_pos(const float& yp) { y_pos = yp; }
	float get_x_pos() const { return x_pos; }
	float get_y_pos() const { return y_pos; }

	void setMapXY(const int& mp_x, const int& mp_y) { map_x = mp_x; map_y = mp_y; }

	//Collision Map
	void doPlayer(Map& gmap);	
	void collisionMap(Map& gmap);

	//Move
	void set_type_move(const int& typeMove) { type_move = typeMove; }
	void setAnimation(const int& pos_a, const int& pos_b) { animationA = pos_a; animationB = pos_b; }
	void set_input_left(const int& ipLeft) { input_type.left = ipLeft; }

	sf::FloatRect getRect();
	void impMoveType(sf::RenderTarget& target);

	//Render
	void update();
	void render(sf::RenderTarget& target);
};