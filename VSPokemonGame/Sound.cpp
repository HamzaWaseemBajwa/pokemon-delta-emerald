#include "Sound.h"
#include <SDL.h>

Mix_Music* Sound::_music = nullptr;
Mix_Chunk* Sound::_cry = nullptr;
Mix_Chunk* Sound::_select = nullptr;
Mix_Chunk* Sound::_general = nullptr;

void Sound::InitlizeMusic()
{
	//Error handlers
	
	int result;
	const int flags = MIX_INIT_OGG;
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("Failed to init SDL\n");
		exit(1);
	}
	Mix_OpenAudio(44100, AUDIO_S32SYS, 2, 1024);
	if (flags != (result = Mix_Init(flags)))
	{
		printf("Could not initialize mixer (result: %d).\n", result);
		printf("Mix_Init: %s\n", Mix_GetError());
		exit(1);
	}

}

void Sound::ChangeMusic(const std::string file_name)
{
	EndMusic();
	_music = Mix_LoadMUS(("Resources/Music/" + file_name).c_str());
	Mix_PlayMusic(_music, -1);
}

void Sound::PlayCry(std::string file_name)
{

	switch (file_name.length())
	{
	case 1:
		file_name = "00" + file_name;
		break;
	case 2:
		file_name = '0' + file_name;
		break;
	default:
		file_name = file_name.substr(0, 3);
		break;
	}
	_cry = Mix_LoadWAV(("Resources/Music/Cries/" + file_name + ".wav").c_str());
	Mix_PlayChannel(-1, _cry, 0);
}

void Sound::PlayInteractSound()
{
	_select = Mix_LoadWAV("Resources/Music/Effects/Select.wav");
	Mix_PlayChannel(-1, _select, 0);

}

void Sound::PlaySound(std::string sound_name)
{
	_general = Mix_LoadWAV(("Resources/Music/Effects/" + sound_name + ".wav").c_str());
	Mix_PlayChannel(-1, _general, 0);
}

void Sound::EndMusic()
{
	Mix_FreeMusic(_music);
	_music = nullptr;
}
