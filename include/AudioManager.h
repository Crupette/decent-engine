/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-11
 *	gcc -std=c++17
 * */

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL_mixer.h>

#include <unordered_map>
#include <string>

#include "Logger.h"

namespace DecentEngine {

class AudioManager;

namespace Audio {

class Sound {
	Mix_Chunk* m_chunk = nullptr;
public:
	friend class DecentEngine::AudioManager;
	void begin(int m_loops = 0);
};

class Music {
	Mix_Music* m_music = nullptr;
public:
	friend class DecentEngine::AudioManager;
	void begin(int m_loops = 0);
	static void end();
	static void pause();
	static void resume();
};

}

class AudioManager {
	static Logger m_logger;

	static std::unordered_map<std::string, Mix_Chunk*> m_sounds;
	static std::unordered_map<std::string, Mix_Music*> m_music;
	bool m_init = false;
public:
	AudioManager() {}
	~AudioManager() { destroy(); }

	void init();
	void destroy();

	Audio::Sound getSound(const std::string& filePath);
	Audio::Music getMusic(const std::string& filePath);
};

}

#endif
