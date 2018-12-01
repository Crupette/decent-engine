/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-11-30
 *	Compiler Used:		g++ -std=c++17
 * */

#ifndef FPSREGULATOR_H
#define FPSREGULATOR_H

#include <cstdint>

namespace DecentEngine {

	/**
	 * @brief Controls the FPS
	 */
class FPSRegulator {
	static uint32_t m_beginningTicks;

	static float m_delta;
	static float m_fps;
public:
	/**
	 * @brief Called at the end of each frame. Regulates the FPS to the given value
	 *
	 * @param maxFPS Maximum FPS for processing
	 */
	static void regulate(uint32_t maxFPS);

	static float getFPS() { return m_fps; }
	static float getDelta() { return m_delta; }
};

}

#endif
