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

	Game::GetInstance()->SetDeltatTime(duration.count());
}
