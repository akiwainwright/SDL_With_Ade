#pragma once
#include <chrono>

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

private:

	std::chrono::steady_clock::time_point m_FrameStart;
	std::chrono::steady_clock::time_point m_FrameEnd;
};

