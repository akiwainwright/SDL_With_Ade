#define SDL_MAIN_HANDLED
#include <iostream>

#include "Game.h"


int main() {

	Game::GetInstance()->StartSDL();

	while (Game::GetInstance()->IsRunning())
	{
		Game::GetInstance()->Upddate();
		Game::GetInstance()->Render();
		Game::GetInstance()->Events();
	}

	return 0;

}
