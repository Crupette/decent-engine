#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "ShaderHandler.h"
#include "Window.h"

namespace DecentEngine {

class Camera {
	glm::vec2 m_position;
	float m_scale;
	float m_rotation;

	glm::mat4 m_orthoMatrix;
	glm::mat4 m_cameraMatrix;

	glm::uvec2 m_lastWindowSize;
	
	bool m_needsUpdate;
public:
	Camera();
	~Camera();

	/**
	 * @brief Initializes the orthomatrix and position, scale, and rotation
	 *
	 * @param position Position of the camera
	 * @param scale Scale to screen
	 * @param rotation Rotation of the camera
	 */
	void init(const glm::vec2& position, float scale, float rotation);

	/**
	 * @brief Refreshes the camera matrix (and ortho matrix if the screen was refreshed)
	 *
	 * @param currentWindow Current window for the camera
	 */
	void update(Window* currentWindow);

	/**
	 * @brief Loads the uniform [cameraMatrix] into the shader
	 *
	 * @param shader Shader program to use
	 */
	void loadUniform(ShaderHandler* shader);

	/**
	 * @brief Returns wether the bounds are within the camera's vision
	 *
	 * @param bounds bounds of the object
	 *
	 * @return wether the object is in the cameras vision
	 */
	bool boundsInFrustrum(const glm::vec4& bounds);

	void setPosition(const glm::vec2& position) { m_position = position; m_needsUpdate = true; }
	void setScale(float scale) { m_scale = scale; m_needsUpdate = true; }
	void setRotation(float rotation) { m_rotation = rotation; m_needsUpdate = true; }

	glm::vec2 getPosition() { return m_position; }
	float getScale() { return m_scale; }
	float getRotation() { return m_rotation; }

	/**
	 * @brief Adds the given [by] value to the [position/scale/rotation]
	 *
	 * @param by added to
	 */
	void translatePosition(const glm::vec2& by) { m_position += by; m_needsUpdate = true; }
	void translateScale(float by) { m_scale += by; m_needsUpdate = true; }
	void translateRotation(float by) { m_rotation += by; m_needsUpdate = true; }
};

}

#endif
