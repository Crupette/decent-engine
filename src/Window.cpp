#include "Window.h"
#include "picoPNG.h"

#include "TextureCache.h"

namespace DecentEngine {

Window::Window() : m_window(nullptr){

}

Window::~Window(){
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

void Window::init(const std::string& title, size_t x, size_t y, size_t width, size_t height, uint32_t flags){
	m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | flags);

	if(m_window == nullptr){
		//TODO: Add logger message with [ERR] tag
		printf("Failed to create window.\n Error is as follows:\n%s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	m_context = SDL_GL_CreateContext(m_window);
	m_dimensions = glm::uvec2(width, height);
}

void Window::swapBuffer(){
	SDL_GL_SwapWindow(m_window);
	m_resized = false;
}

void Window::setIcon(const std::string& filePath){
	std::vector<unsigned char> pixelData;
	size_t width = 0, height = 0;
	TextureCache::getPixelsFromPNG(filePath, pixelData, width, height);

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(&pixelData[0], width, height, 32, 4 * width, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	SDL_SetWindowIcon(m_window, surface);
	SDL_FreeSurface(surface);
}

void Window::resizeEvent(size_t width, size_t height){
	SDL_SetWindowSize(m_window, width, height);
	m_dimensions = glm::uvec2(width, height);

	glViewport(0, 0, width, height);
	m_resized = true;
	//printf("Resized to %lu, %lu\n", width, height);
}

bool Window::wasResized(){
	return m_resized;
}

}
