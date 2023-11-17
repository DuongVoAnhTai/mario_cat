#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define TILE_SIZE 48

#define MAX_X 300 //Number column of the map
#define MAX_Y 21 //Number row of the map

struct Map
{
	//Vi tri dau cua map
	int start_x;
	int start_y;

	//Vi tri hien tai cua map
	int max_x; 
	int max_y;

	//Gia tri cua o
	int tile[MAX_Y][MAX_X];
	char* file_name;
};

//Move state
struct Input {
	int left;
	int right;
	int jump;
};

//Check collison
namespace globalFunc
{
	bool CheckCollision(const sf::FloatRect& object1, const sf::FloatRect& object2);
}