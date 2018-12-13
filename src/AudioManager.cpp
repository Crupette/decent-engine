#include "AudioManager.h"

#include <cstddef>

namespace DecentEngine {

Logger AudioManager::m_logger("AudioManager");

std::unordered_map<std::string, Mix_Chunk*> AudioManager::m_sounds;
std::unordered_map<std::string, Mix_Music*> AudioManager::m_music;

void AudioManager::init(){
	int error = Mix_Init(MIX_INIT_OGG);
	if(error == -1){
		m_logger.log(Logger::Type::ERROR, "Failed to initialize SDL2_mix:", Mix_GetError());
		exit(-1);
	}
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
	m_init = true;
}

void AudioManager::destroy(){
	if(!m_init) return;
	m_init = false;
	Mix_Quit();
}

Audio::Sound AudioManager::getSound(const std::string& filePath){
	auto it = m_sounds.find(filePath);
	Audio::Sound sound;
	if(it == m_sounds.end()){
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
		if(chunk == nullptr){
			m_logger.log(Logger::Type::ERROR, "Failed to load sound", filePath, "(", Mix_GetError(), ")");
			exit(-1);
		}
		m_sounds[filePath] = chunk;
		sound.m_chunk = chunk;
	}else{
		sound.m_chunk = it->second;
	}
	return sound;
}

Audio::Music AudioManager::getMusic(const std::string& filePath){
	auto it = m_music.find(filePath);
	Audio::Music sound;
	if(it == m_music.end()){
		Mix_Music* music = Mix_LoadMUS(filePath.c_str());
		if(music == nullptr){
			m_logger.log(Logger::Type::ERROR, "Failed to load music", filePath, "(", Mix_GetError(), ")");
			exit(-1);
		}
		m_music[filePath] = music;
		sound.m_music = music;
	}else{
		sound.m_music = it->second;
	}
	return sound;
}

void Audio::Sound::begin(int loops){
	if(Mix_PlayChannel(-1, m_chunk, loops) == -1){
		//TODO: DecentEngine::AudioManager::m_logger.log(Logger::Type::ERROR, "Failed to play sound:", Mix_GetError());
	}
}

void Audio::Music::begin(int loops){
	if(Mix_PlayMusic(m_music, loops) == -1){
		//TODO: DecentEngine::AudioManager::m_logger.log(Logger::Type::ERROR, "Failed to play music:", Mix_GetError());
	}
}

void Audio::Music::end(){
	Mix_HaltMusic();
}

void Audio::Music::pause(){
	Mix_PauseMusic();
}

void Audio::Music::resume(){
	Mix_ResumeMusic();
}

}
