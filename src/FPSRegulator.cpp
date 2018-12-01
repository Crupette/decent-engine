#include "FPSRegulator.h"

#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

namespace DecentEngine { 

uint32_t FPSRegulator::m_beginningTicks = 0;

float FPSRegulator::m_fps = 60.f;
float FPSRegulator::m_delta = 1.f / 60.f;

void FPSRegulator::regulate(uint32_t maxFPS) {
	uint32_t difference = SDL_GetTicks() - m_beginningTicks;

	m_fps = 1000.f / difference;
	m_delta = std::min(1.f / (float)(maxFPS), difference / 100.f);

	int skipby = (1000.f / maxFPS) - difference;

	m_beginningTicks = SDL_GetTicks();

	if(skipby > 0){
		SDL_Delay(skipby);
	}
}

}
