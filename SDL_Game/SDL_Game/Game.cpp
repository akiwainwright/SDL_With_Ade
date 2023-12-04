#include "Game.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Callbacks.h"
#include "TextureManager.h"

Game* Game::s_Instance = nullptr;

Game* Game::GetInstance()
{
    if (!s_Instance)
    {
        s_Instance = new Game();
    }

    return s_Instance;
}

Game::Game()
{
    m_DeltaTime = 0.16;

    m_Running = true;

    m_Window = nullptr;
    m_Renderer = nullptr;
}

bool Game::StartSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        Callbacks::LogSDLError("Failed To Initialise SDL");
        return false;
    }

    m_Window = SDL_CreateWindow("SDL_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        Callbacks::LogSDLError("Failed To Create Window");
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_Renderer)
    {
        Callbacks::LogSDLError("Failed To Create Renderer");
        return false;
    }

    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 247, 255);

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        Callbacks::LogIMGError("Failed To Initialise SDL_Image");
        return false;
    }

    if (!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        Callbacks::LogSDLError("Failed To Initialise SDL_Mixer");
        return false;
    }

    if (Mix_OpenAudio(44000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Callbacks::LogSDLError("Failed To Open Audio");
        return false;
    }

    return true;
}

bool Game::LoadAssets()
{

    return TextureManager::GetInstance()->LoadTextures();
}

void Game::Upddate()
{
   
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 247, 255);
    SDL_RenderClear(m_Renderer);

    //TextureManager::GetInstance()->DrawTexture("Spider_Dance_soundtrack.png", 200, 200, 640, 480);
    TextureManager::GetInstance()->DrawSpriteFrame("Skeleton enemy.png", 200, 200, 832, 320, 5, 13, 1, 5);

    SDL_RenderPresent(m_Renderer);
}

void Game::Events()
{
    SDL_PollEvent(&m_Events);

    switch (m_Events.type)
    {
    case SDL_QUIT:
        m_Running = false;
        break;
    default:
        break;
    }
}

Game::~Game()
{
    s_Instance = nullptr;
    delete s_Instance;

    
}
