#include "global.cpp"
#include "game.h"

int main() {
	Game game;

	//game loop
	while (game.running()) {

		//update
		game.update();

		//render
		game.render();
	}
	return 0;
}