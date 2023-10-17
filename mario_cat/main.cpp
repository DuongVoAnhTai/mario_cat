#include <iostream>
#include "game.h"

int main() {
	game game;

	//game loop
	while (game.running()) {

		//update
		game.update();

		//render
		game.render();
	}
	return 0;
}