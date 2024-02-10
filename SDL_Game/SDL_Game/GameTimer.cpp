#include "GameTimer.h"
#include "Game.h"

GameTimer::GameTimer()
{
	m_FrameStart = std::chrono::steady_clock::now();
}

GameTimer::~GameTimer()
{
	m_FrameEnd = std::chrono::steady_clock::now();

	std::chrono::duration<float> duration = m_FrameEnd - m_FrameStart;

	//Game::GetInstance()->SetDeltatTime(duration.count());
}

GameTime* GameTime::s_Instance = nullptr;

GameTime* GameTime::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new GameTime();
	}

	return s_Instance;
}

using namespace std::chrono;

GameTime::GameTime()
{
	m_CurrentFrame = high_resolution_clock::now();
}

float GameTime::GetDeltaTime()
{
	steady_clock::time_point lastFrameTime = m_CurrentFrame;

	m_CurrentFrame = high_resolution_clock::now();

	duration<float> deltaTime = m_CurrentFrame - lastFrameTime;


	return deltaTime.count();
}
