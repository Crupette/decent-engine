/*
 * File:		DecentEngine.h
 * Description:		Header file that holds basic version information and other simple functions
 *
 * Created:		2018-11-3
 * By:			Jon Santmyer
 * 			jonsantmyer@gmail.com
 *
 * Used Compiler:	gcc
*/

#ifndef DECENTENGINE_H
#define DECENTENGINE_H

#include "Logger.h"

namespace DecentEngine {
	
	#define VERSION "0.1.0"

	Logger baseLogger("DecentEngine");

	/**
	 * @brief Logs the version of the engine that the game is using
	 */
	void engine_init() {
		baseLogger.log(Logger::Type::INFO, "Using decent-engine version", VERSION);
	}

};

#endif
