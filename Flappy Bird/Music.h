#pragma once
#include <SDL_mixer.h>

class Music
{
    private:
        Mix_Music* LongSound;
        Mix_Chunk* ShortSound;
    public:
        void loadMusic(const char* adress);
        void loadChunk(const char* adress);
        void playMusic();
        void pauseMusic();
        void resumeMusic();
        void playChunk();
};
