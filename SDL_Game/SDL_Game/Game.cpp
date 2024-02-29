
#include "Game.h"
#include <SDL_image.h>
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

Game::Game()
:m_Window(nullptr)
,m_Renderer(nullptr)
,m_IsRunning(true)
,m_UpdatingActors(false)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	m_Window = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
	if (!m_Window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_Renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	m_TicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (m_IsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	int mouseX, mouseY ;
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_IsRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:

				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					SDL_GetMouseState(&mouseX, &mouseY);
					//cout << mouseX << " " << mouseY << endl;
					m_Ship->SetTarget(Vector2(mouseX, mouseY));
					break;
				}
				break;
			case SDL_KEYDOWN:
				break;
		}
	}
	

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_IsRunning = false;
	}

	for (auto actors : m_Actors)
	{
		GameObject* obj = dynamic_cast<GameObject*>(actors);
		if (obj)
		{
			obj->ProcessInput(state);
		}
	}
}

//THIS IS JUST TO SHOW HOW TO USE MOUSE INPUT 
void Game::ProcessMouseInput()
{
	int mouseX, mouseY;
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_IsRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT://LEFT MOUSE BUTTON
				break;
			case SDL_BUTTON_RIGHT://RIGHT MOUSE BUTTON
				break;
			case SDL_BUTTON_MIDDLE://MIDDLE MOUSE BUTTON
				break;
			}
			break;
		case SDL_MOUSEMOTION://active mouse movement

			//cout << mouseX << " " << mouseY << endl;
			break;
		case SDL_MOUSEWHEEL:// mouse wheel scroll movement
			if (event.wheel.y > 0)//mouse wheel is scrolling up
			{

			}
			if (event.wheel.y < 0)//mouse wheel is scrolling down
			{

			}
			break;

		}
	}

	if (SDL_GetMouseState(&mouseX, &mouseY) && SDL_BUTTON_LEFT)// holding left mouse button
	{
		cout << "sdl" << endl;
	}
	

}

void Game::UpdateGame()
{
	
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	m_TicksCount = SDL_GetTicks();

	MessageDispatcher::Instance()->DispatchDelayedMessages();
	// Update all actors
	m_UpdatingActors = true;
	for (auto actor : m_Actors)
	{
		actor->Update(deltaTime);
	}
	m_UpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : m_PendingActors)
	{
		m_Actors.emplace_back(pending);
	}
	m_PendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : m_Actors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_Renderer);
	
	// Draw all sprite components
	for (auto sprite : m_Sprites)
	{
		sprite->Draw(m_Renderer);
	}

	SDL_RenderPresent(m_Renderer);
}

void Game::LoadData()
{
	// Create  ship
	m_Ship = new Ship(this, "ship", Actor::EActive);
	m_Ship->GetTransform()->SetPosition(Vector2(100.0f, 384.0f));
	m_Ship->GetTransform()->SetScale(Vector2(1.5f, 1.5f));

	//// Create actor for the background (this doesn't need a subclass)
	//Actor* temp = new Actor(this);
	//temp->SetPosition(Vector2(512.0f, 384.0f));
	//// Create the "far back" background
	//BGSpriteComponent* bg = new BGSpriteComponent(temp);
	//bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	//std::vector<SDL_Texture*> bgtexs = {
	//	GetTexture("Assets/Farback01.png"),
	//	GetTexture("Assets/Farback02.png")
	//};
	//bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);
	//// Create the closer background
	//bg = new BGSpriteComponent(temp, 50);
	//bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	//bgtexs = {
	//	GetTexture("Assets/Stars.png"),
	//	GetTexture("Assets/Stars.png")
	//};
	//bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!m_Actors.empty())
	{
		delete m_Actors.back();
	}

	// Destroy textures
	for (auto i : m_Textures)
	{
		SDL_DestroyTexture(i.second);
	}
	m_Textures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = m_Textures.find(fileName);
	if (iter != m_Textures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(m_Renderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		m_Textures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

Actor* Game::GetActor(Actor* _actor)
{
	return nullptr;
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (m_UpdatingActors)
	{
		m_PendingActors.emplace_back(actor);
	}
	else
	{
		m_Actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(m_PendingActors.begin(), m_PendingActors.end(), actor);
	if (iter != m_PendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, m_PendingActors.end() - 1);
		m_PendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(m_Actors.begin(), m_Actors.end(), actor);
	if (iter != m_Actors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, m_Actors.end() - 1);
		m_Actors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = m_Sprites.begin();
	for ( ;
		iter != m_Sprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	m_Sprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);
	m_Sprites.erase(iter);
}
