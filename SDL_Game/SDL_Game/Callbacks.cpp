#include "Callbacks.h"
#include <SDL.h>
#include <SDL_image.h>

void Callbacks::LogSDLError(std::string message)
{
	std::cout << message << " " << SDL_GetError() << "\n";
}

void Callbacks::LogIMGError(std::string message)
{
	std::cout << message << " " << IMG_GetError() << "\n";
}
