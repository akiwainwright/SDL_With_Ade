#define SDL_MAIN_HANDLED
#include <iostream>

#include "Game.h"
#include "GameTimer.h"


int main() {

	Game::GetInstance()->SetRunning(Game::GetInstance()->StartSDL());
	Game::GetInstance()->SetRunning(Game::GetInstance()->LoadAssets());

	while (Game::GetInstance()->IsRunning())
	{
		GameTimer timer;

		Game::GetInstance()->Upddate();
		Game::GetInstance()->Render();
		Game::GetInstance()->Events();
	}

	return 0;

}
