/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-2
 *	Compiler:		gcc -std=c++17
 * */

#ifndef RENDERER_DEFAULT_H
#define RENDERER_DEFAULT_H

#include "ShaderHandler.h"
#include "SpriteBatch.h"
#include "Object.h"
#include "Camera.h"

namespace DecentEngine	{

class RendererDefault {
	static ShaderHandler* m_shader;
	static SpriteBatch m_batch;
public:
	/**
	 * @brief Initializes the renderer. This is called in Base's init method
	 */
	static void init();
	/**
	 * @brief Destroys the renderer's parts. This is called in the Base's destroy method
	 */
	static void destroy();
	/**
	 * @brief Starts up the shaders and batch.
	 *
	 * @param camera Camera passes to the shaders
	 */
	static void begin(Camera& camera);
	static void beginShader(Camera& camera);
	/**
	 * @brief Ends the rendering process and actually draws the glyphs
	 */
	static void end();
	static void endShader();
	/**
	 * @brief Adds object and possibly bounding boxes to the SpriteBatch. Call this after the begin method
	 *
	 * @param object Object to add
	 * @param renderBB If the bounding boxes are rendered. Default:true
	 */
	static void addObject(Object* object, bool renderBB = false);
	/**
	 * @brief Adds sprite to SpriteBatch. call this after the begin method
	 *
	 * @param sprite Sprite to add
	 */
	static void addSprite(Sprite* sprite);
};

}

#endif
