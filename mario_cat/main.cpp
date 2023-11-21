#include "global.h"
#include "game.h"

int main()
{	
	Game game;

	//game loop
	while (game.running())
	{
		//music
		game.music();

		//update
		game.update();

		//render
		game.render();

	}
	return 0;
}