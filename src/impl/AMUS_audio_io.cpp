#include "../incl/AMUS_audio_io.hpp"

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_audio.h"

using namespace std;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO);
    cout << SDL_INIT_AUDIO << endl;
    cout << &SDL_Init << endl;
    return 0;
}