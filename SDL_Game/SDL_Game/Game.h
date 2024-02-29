
#pragma once
#include <SDL.h>
#include "BasicIncludes.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	class Actor* GetActor(class Actor* _actor);

	void AddActor(class Actor* _actor);
	void RemoveActor(class Actor* _actor);

	void AddSprite(class SpriteComponent* _sprite);
	void RemoveSprite(class SpriteComponent* _sprite);
	
	SDL_Texture* GetTexture(const std::string& _fileName);
private:
	void ProcessInput();
	void ProcessMouseInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> m_Textures;

	// All the actors in the game
	std::vector<class Actor*> m_Actors;
	// Any pending actors
	std::vector<class Actor*> m_PendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> m_Sprites;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Uint32 m_TicksCount;
	bool m_IsRunning;
	// Track if we're updating actors right now
	bool m_UpdatingActors;

	class Ship* m_Ship; // Player's ship
};
