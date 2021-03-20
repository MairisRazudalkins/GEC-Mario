#pragma once
#include <SDL_mixer.h>
#include <string>

class AudioManager
{

public:
	static void PlayMusic(Mix_Music* music, int loops = -1);
	static void PlayClip(Mix_Chunk* clip, int loops = 0);
	static Mix_Music* LoadMusic(std::string path);
	static Mix_Chunk* LoadClip(std::string path);
};
