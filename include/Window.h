#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

namespace DecentEngine {

class Window {
	SDL_Window* m_window;
	SDL_GLContext m_context;

	bool m_resized = false;

	glm::uvec2 m_dimensions;
public:
	Window();
	~Window();

	/**
	 * @brief Initializes a SDL_Window and SDL_GLContext instance 
	 *
	 * @param title String rendered at top of window
	 * @param x X coordinate of window
	 * @param y Y coordinate of window
	 * @param width Width of window
	 * @param height Height of window
	 * @param flags Additional flags (eg SDL_WINDOW_FULLSCREEN)
	 */
	void init(const std::string& title, size_t x, size_t y, size_t width, size_t height, uint32_t flags);

	/**
	 * @brief Swaps the window buffer.
	 */
	void swapBuffer();
	/**
	 * @brief Reciever for the SDL_ResizeEvent event
	 *
	 * @param width Width of new size
	 * @param height Height of the new size
	 */
	void resizeEvent(size_t width, size_t height);

	/**
	 * @brief Returns whether the window was resized
	 */
	bool wasResized();
	glm::uvec2 getSize() {return m_dimensions; }
};

}

#endif
