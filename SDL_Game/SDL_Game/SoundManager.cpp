#include "SoundManager.h"
#include <filesystem>

#include "Callbacks.h"

namespace fs = std::filesystem;

SoundManager* SoundManager::s_Instance = nullptr;

SoundManager* SoundManager::GetInstance()
{
    if (!s_Instance)
    {
        s_Instance = new SoundManager();
    }

    return s_Instance;
}

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
}

bool SoundManager::LoadSoundtrack()
{
    std::string path = "Assets/Audio/Soundtrack";

    for (const fs::directory_entry entry : fs::directory_iterator(path))
    {
        m_Soundtrack[Callbacks::FileNameToString(entry)] = Mix_LoadMUS(entry.path().string().c_str());

        if (!m_Soundtrack[Callbacks::FileNameToString(entry)])
        {
            Callbacks::LogMIXError("Failed to load track " + Callbacks::FileNameToString(entry));
            return false;
        }
    }

    return true;
}

bool SoundManager::LoadSFX()
{
    std::string path = "Assets/Audio/SFX";

    for (const fs::directory_entry entry : fs::directory_iterator(path))
    {
        m_Soundtrack[Callbacks::FileNameToString(entry)] = Mix_LoadMUS(entry.path().string().c_str());

        if (!m_Soundtrack[Callbacks::FileNameToString(entry)])
        {
            Callbacks::LogMIXError("Failed to load SFX " + Callbacks::FileNameToString(entry));
            return false;
        }
    }

    return true;
}

void SoundManager::PlayTrack(std::string fileName)
{
    if (Mix_PlayMusic(m_Soundtrack[fileName], -1) == -1)
    {
        Callbacks::LogSDLError("Failed to Play " + fileName);
    }
}

void SoundManager::PlaySFX(std::string fileName)
{
    if (Mix_PlayChannel(-1, m_GameSFX[fileName], 0) == -1)
    {
        Callbacks::LogSDLError("Failed to Play " + fileName);
    }
}
