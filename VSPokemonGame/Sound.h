#pragma once

#include <SDL_mixer.h>
#include <string>

class Sound
{
	static Mix_Music* _music; 
	static Mix_Chunk* _cry;
	static Mix_Chunk* _select;
	static Mix_Chunk* _general;
public:
	static void InitlizeMusic(); //Prepare for music playing 
	static void ChangeMusic(std::string file_name); //change music to passed filename
	static void PlayCry(std::string file_name); //change music to passed filename
	static void PlayInteractSound();
	static void PlaySound(std::string sound_name);
	static void EndMusic(); //End currently playing music
	~Sound() = default;
private:
	Sound() = default; //private construtor, in effect making this a static class
};

