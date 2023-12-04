#include "TextureManager.h"
#include <filesystem>

#include "Callbacks.h"
#include "Game.h"

namespace fs = std::filesystem;

TextureManager* TextureManager::s_Instance = nullptr;

TextureManager* TextureManager::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new TextureManager();
	}

	return s_Instance;
}

bool TextureManager::LoadTextures()
{
	std::string path = "Assets/Textures";

	for (const fs::directory_entry entry : fs::directory_iterator(path))
	{
		SDL_Surface* textureSurface = IMG_Load(entry.path().string().c_str());

		if (!textureSurface)
		{
			Callbacks::LogSDLError("Failed To Load Image");
			return false;
		}

		m_Textures[Callbacks::FileNameToString(entry)] = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), textureSurface);

		SDL_FreeSurface(textureSurface);
	}

	return true;
}

void TextureManager::DrawTexture(std::string textureFileName, float xPos, float yPos, float width, float height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = {0, 0, width, height};
	SDL_Rect dstRect = {xPos, yPos, width, height};
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_Textures[textureFileName], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawSpriteFrame(std::string fileName, float xPos, float yPos, float spriteSheetWidth, float spriteSheetHeight, float totalRows, int totalColumns, int frameRow, int frameColumn, SDL_RendererFlip flip)
{
	float frameWidth = spriteSheetWidth / totalColumns;
	float frameHeight = spriteSheetHeight / totalRows;

	SDL_Rect srcRect = { frameWidth * (frameColumn -1), frameWidth * (frameRow - 1), frameWidth, frameHeight};
	SDL_Rect dstRect = { xPos, yPos, frameWidth, frameHeight };
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), m_Textures[fileName], &srcRect, &dstRect, 0, nullptr, flip);
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
}
