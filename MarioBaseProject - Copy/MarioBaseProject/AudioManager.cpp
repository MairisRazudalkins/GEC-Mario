#include <iostream>
#include "AudioManager.h"

void AudioManager::PlayMusic(Mix_Music* music, int loops)
{
	Mix_PlayMusic(music, loops);
}

void AudioManager::PlayClip(Mix_Chunk* clip, int loops)
{
	if (Mix_Playing(clip->allocated))
		Mix_HaltChannel(clip->allocated);
	
	Mix_PlayChannel(-1, clip, loops);
}

Mix_Music* AudioManager::LoadMusic(std::string path)
{
	path = "Sounds/" + path;
	
	Mix_Music* music = Mix_LoadMUS(path.c_str());

	if (music == nullptr)
	{
		std::cout << "Failed to load!" << Mix_GetError() << std::endl;
		return nullptr;
	}
	
	return music;
}

Mix_Chunk* AudioManager::LoadClip(std::string path)
{
	path = "Sounds/" + path;
	
	Mix_Chunk* clip = Mix_LoadWAV(path.c_str());

	if (clip == nullptr)
	{
		std::cout << "Failed to load!" << Mix_GetError() << std::endl;
		return nullptr;
	}

	return clip;
}
