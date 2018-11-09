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
	
	#define VERSION "0.1.2"

    extern Logger baseLogger;

	/**
	 * @brief Logs the version of the engine that the game is using
	 */
    extern void engine_init();

};

#endif
