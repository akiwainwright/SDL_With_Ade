#pragma once
#include <SDL_mixer.h>
#include <map>
#include <string>

class SoundManager
{
public:
	static SoundManager* GetInstance();

	~SoundManager();

	bool LoadSoundtrack();
	bool LoadSFX();

	void PlayTrack(std::string fileName);
	void PlaySFX(std::string fileName);

private:
	static SoundManager* s_Instance;

	std::map<std::string, Mix_Music*> m_Soundtrack;
	std::map<std::string, Mix_Chunk*> m_GameSFX;

	SoundManager();

};

