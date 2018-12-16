#include "Base.h"
#include "InputManager.h"
#include "FPSRegulator.h"
#include "RendererDefault.h"
#include "GuiManager.h"
#include "ParticleEngine.h"

namespace DecentEngine {

Window Base::m_mainWindow;
std::vector<Screen*> Base::m_screens;
size_t Base::m_screenIndex;
uint32_t Base::m_maxFPS;
GameState Base::m_state = GameState::RUN;
Logger Base::logger("Base");

void Base::init(const std::string& name, size_t x, size_t y, size_t width, size_t height, uint32_t maxFPS, uint32_t flags){
	engine_init();	
	
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	m_mainWindow.init(name, x, y, width, height, flags);

	glewExperimental = true;

	GLenum glewReturn = glewInit();
	if(glewReturn != GLEW_OK){
		logger.log(Logger::Type::ERROR, "Failed to initialize GLEW.\nError is as follows:\n", glewGetErrorString(glewReturn));
		SDL_Quit();
		exit(3);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//TODO: Add logger message with [DEBUG] tag
	logger.log(Logger::Type::DEBUG, "VENDOR:    ", glGetString(GL_VENDOR));
	logger.log(Logger::Type::DEBUG, "RENDERER:  ", glGetString(GL_RENDERER));
	logger.log(Logger::Type::DEBUG, "VERSION:   ", glGetString(GL_VERSION));
	logger.log(Logger::Type::DEBUG, "OS:        ", getOS().c_str());

	engine_postgl_init();

    if(m_screens.size() < 1){
        logger.log(Logger::Type::ERROR, "No screens were initialized for the engine! Tell your local developer that its a problem!", "Error 44");
		SDL_Quit();
		exit(44);
    }
    
	GuiManager::init();

	for(Screen* screen : m_screens){
		screen->init();
	}

	m_maxFPS = maxFPS;
	RendererDefault::init();
		
	gameLoop();
}

void Base::destroy(){
	for(Screen* screen : m_screens){
		screen->destroy();
		delete screen;
	}
	RendererDefault::destroy();
	ParticleEngine::destroy();
}

void Base::addScreen(Screen* screen){
	m_screens.push_back(screen);
}

Screen* Base::getScreen(size_t index){
	if(index > m_screens.size()){
		//TODO: Add logger message with [ERR] tag
		printf("Failed to return screen at index %lu.\nError is as follows:\nIndex out of range (attempted to retrieve index %lu/%lu\n", index, index, m_screens.size());
		SDL_Quit();
		exit(4);
	}
	return m_screens[index];
}

void Base::setCurrentScreen(size_t index){
	if(index > m_screens.size()){
		//TODO: Add logger message with [ERR] tag
		printf("Failed to return screen at index %lu.\nError is as follows:\nIndex out of range (attempted to retrieve index %lu/%lu\n", index, index, m_screens.size());
		SDL_Quit();
		exit(4);
	}
	m_screenIndex = index;
}

void Base::gameLoop(){
	while(m_state != GameState::EXIT){
		processInputs();
		update();
		render();
		FPSRegulator::regulate(m_maxFPS);
	}
	destroy();
}

void Base::update(){
	m_screens[m_screenIndex]->update();
	GuiManager::update();
	ParticleEngine::update();
}

void Base::processInputs(){
	InputManager::update();
	SDL_Event evnt;
	while(SDL_PollEvent(&evnt)){
		switch(evnt.type){
			case SDL_KEYDOWN:
				InputManager::pressKey(evnt.key.keysym.sym);
			break;
			case SDL_KEYUP:
				InputManager::releaseKey(evnt.key.keysym.sym);
			break;
			case SDL_MOUSEBUTTONDOWN:
				InputManager::pressKey(evnt.button.button);
			break;
			case SDL_MOUSEBUTTONUP:
				InputManager::releaseKey(evnt.button.button);
			break;
			case SDL_MOUSEMOTION:
				InputManager::moveMouse(evnt.motion.x, evnt.motion.y);
			break;
			case SDL_MOUSEWHEEL:
				InputManager::scrollWheel(evnt.wheel.y);
			break;
			case SDL_QUIT:
				setState(GameState::EXIT);
			break;
			case SDL_WINDOWEVENT:
				switch(evnt.window.event){
					case SDL_WINDOWEVENT_RESIZED:
						m_mainWindow.resizeEvent(evnt.window.data1, evnt.window.data2);
					break;
				}
			break;
		}
	}
}

void Base::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_screens[m_screenIndex]->render();
	GuiManager::render();
	ParticleEngine::render();

	m_mainWindow.swapBuffer();
}

/*########################################----ETC FUNCTIONS----#########################################*/

std::string getOS() {
	#ifdef _WIN32
		return "Windows 32-bit";
	#elif _WIN64
		return "Windows 64-bit";
	#elif __APPLE__ || __MACH__
		return "Inferior (Mac OSX)";
	#elif __linux__
		struct utsname uts;
		uname(&uts);
		return uts.version;
	#elif __FreeBSD__
		return "FreeBSD";
	#else
		return "Unknown Operating System";
	#endif
}

}
