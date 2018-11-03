#include "Camera.h"
#include "Base.h"

#include <glm/gtc/matrix_transform.hpp>

namespace DecentEngine {

Camera::Camera() : m_position(0.f), m_scale(1.f), m_rotation(0.f), m_orthoMatrix(0.f), m_cameraMatrix(1.f), m_needsUpdate(true) {

}

Camera::~Camera() {

}

void Camera::init(const glm::vec2& position, float scale, float rotation){
	m_position = position;
	m_scale = scale;
	m_rotation = rotation;

	glm::uvec2 screendims = Base::getWindow()->getSize();
	m_orthoMatrix = glm::ortho(-(float)(screendims.x / 2.f), (float)(screendims.x / 2.f), -(float)(screendims.y / 2.f), (float)(screendims.y / 2.f));
}

void Camera::update(Window* currentWindow){
	if(Base::wasScreenResized()){
		glm::uvec2 screendims = currentWindow->getSize();
		m_orthoMatrix = glm::ortho(-(float)(screendims.x / 2.f), (float)(screendims.x / 2.f), -(float)(screendims.y / 2.f), (float)(screendims.y / 2.f));
		printf("Resized window to %u, %u\n", screendims.x, screendims.y);
		m_needsUpdate = true;
	}
	if(m_needsUpdate){
		glm::vec3 translate(-m_position.x, -m_position.y, 0.f);
		m_cameraMatrix = glm::scale(m_orthoMatrix, glm::vec3(m_scale, m_scale, 0.f));
		m_cameraMatrix = glm::translate(m_cameraMatrix, translate);

		m_needsUpdate = false;
	}
}

void Camera::loadUniform(ShaderHandler* shader){
	glUniformMatrix4fv(shader->getUniformLocation("cameraMatrix"), 1, GL_FALSE, &(m_cameraMatrix[0][0]));
}

}
