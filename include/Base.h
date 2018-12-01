#ifndef BASE_H
#define BASE_H

#ifdef __linux__
#include <sys/utsname.h>
#endif

#include "Window.h"
#include "Screen.h"
#include "Logger.h"
#include "DecentEngine.h"

#include <vector>
#include <cstdint>

namespace DecentEngine {

enum class GameState {RUN, PAUSE, EXIT};

class Base{
	static Window m_mainWindow;
	
	static std::vector<Screen*> m_screens;
	static size_t m_screenIndex;	

	static uint32_t m_maxFPS;
	
	static GameState m_state;

	/**
	 * @brief Game loop of entire game
	 */
	static void gameLoop();
	/**
	 * @brief Update the screens
	 */
	static void update();
	/**
	 * @brief Update the InputManager
	 */
	static void processInputs();
	/**
	 * @brief Update the screen
	 */
	static void render();
public:
	static Logger logger;
	/**
	 * @brief Initializes the engine
	 *
	 * @param name Title of the main window
	 * @param x X coordinate of the main window
	 * @param y Y coordinate of the main window
	 * @param width Width of the main window
	 * @param height Height of the main window
	 * @param maxFPS Maximum FPS the window renders at. Can be changed later
	 * @param flags Additional flags for the main window
	 */
	static void init(const std::string& name, size_t x, size_t y, size_t width, size_t height, uint32_t maxFPS, uint32_t flags);
	/**
	 * @brief Destroys all objects and screens.
	 */
	static void destroy();
	/**
	 * @brief Adds a screen to the current screen list
	 *
	 * @param screen Screen to be added.
	 */
	static void addScreen(Screen* screen);
	/**
	 * @brief Returns the screen at index
	 *
	 * @param index ID of the screen
	 *
	 * @return the screen.
	 */
	static Screen* getScreen(size_t index);
	/**
	 * @brief Sets the current screen to screen at index [index]
	 *
	 * @param index screen ID to set to
	 */
	static void setCurrentScreen(size_t index);
	/**
	 * @brief Sets the game state {RUN, PAUSE, EXIT}
	 *
	 * @param state set to
	 */
	static void setState(GameState state) {m_state = state;}
	static GameState getState() {return m_state; }

	/**
	 * @brief Returns whether the screen was resized this frame
	 */
	static bool wasScreenResized() {return m_mainWindow.wasResized();}

	static Window* getWindow() {return &m_mainWindow; }

	static void setMaxFPS(uint32_t max) { m_maxFPS = max; }
};

std::string getOS();

}

#endif
