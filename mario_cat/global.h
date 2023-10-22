#include <iostream>
using namespace std;

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define TILE_SIZE 64

#define MAX_X 400 //Number column of the map
#define MAX_Y 15 //Number row of the map

struct Map
{
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_X][MAX_Y];
	char* file_name;
};