#include "Callbacks.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

void Callbacks::LogSDLError(std::string message)
{
	std::cout << message << " " << SDL_GetError() << "\n";
}

void Callbacks::LogIMGError(std::string message)
{
	std::cout << message << " " << IMG_GetError() << "\n";
}

void Callbacks::LogMIXError(std::string message)
{
	std::cout << message << " " << Mix_GetError() << "\n";
}

std::string Callbacks::FileNameToString(std::filesystem::directory_entry entry)
{
	return entry.path().filename().string();
}
