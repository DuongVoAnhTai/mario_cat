#include "global.h"
#include "tileMap.h"
//#include "tile.h"

GameMap::GameMap() 
{
	game_map.start_x = 0;
	game_map.start_y = 0;
	game_map.max_x = 0;
	game_map.max_y = 0;
	game_map.file_name = nullptr;

	this->size = sf::VideoMode::getDesktopMode();
	//this->tileSheet = NULL;
	//this->tile_mat = new TileMat[MAX_TILE];
}

GameMap::~GameMap() 
{ 
	//delete[] this->tile_mat;
}

void GameMap::loadMap(char* name)
{
	FILE* fp = NULL;
	fopen_s(&fp, name, "rb");
	if (fp == NULL) 
	{
		return;
	}

	/*game_map.max_x = 0;
	game_map.max_y = 0;*/

	for (int i = 0; i < MAX_Y; i++)
	{
		for (int j = 0; j < MAX_X; j++) 
		{
			fscanf_s(fp, "%d", &game_map.tile[i][j]);
			int val = game_map.tile[i][j];
			if (val > 0)
			{
				if (j > game_map.max_x)
				{
					game_map.max_x = j;
				}

				if (i > game_map.max_y)
				{
					game_map.max_y = i;
				}
			}
		}
	}

	game_map.max_x = (game_map.max_x + 1) * TILE_SIZE;
	game_map.max_y = (game_map.max_y + 1) * TILE_SIZE;

	/*game_map.start_x = 0;
	game_map.start_y = 0;*/

	game_map.file_name = name;
	fclose(fp);
}

void GameMap::update()
{
	char file_img[30];
	FILE* fp = NULL;

	for (int i = 0; i < MAX_TILE; i++)
	{
		sprintf_s(file_img, "PNG_file/%d.png", i);

		fopen_s(&fp, file_img, "rb");
		if (fp == NULL)
		{
			continue;
		}
		fclose(fp);

		tile_mat[i].loadIMG(file_img);
	}
}

void GameMap::render(sf::RenderTarget& target)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int map_x = 0;
	int map_y = 0;

	map_x = game_map.start_x / TILE_SIZE;
	x1 = (game_map.start_x % TILE_SIZE) * -1;
	x2 = x1 + this->size.width + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = game_map.start_y / TILE_SIZE;
	y1 = (game_map.start_y % TILE_SIZE) * -1;
	y2 = y1 + this->size.height + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = game_map.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			if ((map_x >= 0 && map_x < MAX_X) && (map_y >= 0 && map_y < MAX_Y))
			{
				int val = game_map.tile[map_y][map_x];
					cout << val << endl;
				if (val > 0)
				{
					tile_mat[val].setRect(j, i);
					tile_mat[val].render(target);
				}
			}
			map_x++;
		}
		map_y++;
	}
}