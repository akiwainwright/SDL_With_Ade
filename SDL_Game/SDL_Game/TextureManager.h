#pragma once
#include <SDL_image.h>
#include <map>
#include <string>


/*
class TextureManager
{
public:
	static TextureManager* GetInstance();

	bool LoadTextures();

	void DrawTexture(std::string fileName, float xPos, float yPos, float width, float height, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void DrawSpriteFrame(std::string fileName, float xPos, float yPos, 
		float spriteSheetWidth, float spriteSheetHeight, float totalRows, int totalColumn, int frameRow, int frameColumn, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	~TextureManager();

private:
	static TextureManager* s_Instance;

	std::map<std::string, SDL_Texture*> m_Textures;

	TextureManager();
};

*/