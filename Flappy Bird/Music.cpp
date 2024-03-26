#include "Music.h"

void Music::loadMusic(const char* adress)
{
    LongSound = Mix_LoadMUS(adress);
}

void Music::loadChunk(const char* adress)
{
    ShortSound = Mix_LoadWAV(adress);
}

void Music::playMusic()
{
    Mix_PlayMusic(LongSound, -1);
}

void Music::pauseMusic()
{
    Mix_PauseMusic();
}

void Music::resumeMusic()
{
    Mix_ResumeMusic();
}

void Music::playChunk()
{
    Mix_PlayChannel(-1, ShortSound, 0);
}
