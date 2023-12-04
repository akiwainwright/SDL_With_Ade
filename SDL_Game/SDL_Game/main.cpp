#define SDL_MAIN_HANDLED
#include <iostream>

#include "Game.h"
#include "GameTimer.h"
#include "SoundManager.h"


int main() {

	Game::GetInstance()->SetRunning(Game::GetInstance()->StartSDL());
	Game::GetInstance()->SetRunning(Game::GetInstance()->LoadAssets());

	SoundManager::GetInstance()->PlayTrack("07.Helter Skelter.mp3");

	while (Game::GetInstance()->IsRunning())
	{
		GameTimer timer;

		Game::GetInstance()->Upddate();
		Game::GetInstance()->Render();
		Game::GetInstance()->Events();
	}

	return 0;

}
