#pragma once

#include <SDL.h>

constexpr int windowWidth = 1280;
constexpr int windowHeight = 720;

class Game
{
public:
	static Game* GetInstance();

	inline bool IsRunning() { return m_Running; }
	inline void SetRunning(bool runState) { m_Running = runState; }

	inline float GetDeltaTime() { return m_DeltaTime; }
	inline void SetDeltatTime(float dt) { m_DeltaTime = dt; }

	inline SDL_Window* GetWindow() { return m_Window; }
	
	inline SDL_Renderer* GetRenderer() { return m_Renderer; }

	bool StartSDL();

	bool LoadAssets();

	void Upddate();
	void Render();
	void Events();

	~Game();

private:
	bool m_Running;

	float m_DeltaTime;

	static Game* s_Instance;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Event m_Events;

	Game();
};

