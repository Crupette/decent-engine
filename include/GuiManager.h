/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-4
 *	Compiler:		gcc --std=c++17
 * */

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "ShaderHandler.h"
#include "Camera.h"
#include "Gui.h"

#include <string>
#include <unordered_map>

namespace DecentEngine {

class GuiManager {
	static Camera m_camera;

	typedef std::unordered_map<std::string, Gui*> GuiMap;
	typedef std::unordered_map<std::string, bool> ActiveIdMap;

	static GuiMap m_guis;
	static ActiveIdMap m_active;
public:
	/**
	 * @brief Initializes the camera. Called before screen initialization, after general initialization
	 */
	static void init();
	/**
	 * @brief Destroys the guis. Called after screen destruction
	 */
	static void destroy();

	/**
	 * @brief Updates the currently active GUI
	 */
	static void update();
	/**
	 * @brief Renders the currently active GUI
	 */
	static void render();

	/**
	 * @brief Adds a gui to later be activated
	 *
	 * @param id id to add
	 * @param gui Gui to add.
	 */
	static void addGui(const std::string& id, Gui* gui);
	/**
	 * @brief Activates or deactivates the GUI, can affect others if the gui is of type INTERRUPT
	 *
	 * @param id id of gui
	 * @param mode activate or deactivate
	 *
	 * @return wether it was sucessful
	 */
	static bool setGui(const std::string& id, bool mode);
};

}

#endif
