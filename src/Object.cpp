#include "Object.h"
#include "FPSRegulator.h"

namespace DecentEngine {

Object::Object() : m_velocity(0.f), m_rotVelocity(0.f) {

}

Object::~Object() {

}

void Object::init(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, float rotation, float rotVelocity, const std::string& texture){
	init(position, size, rotation, texture);
	m_velocity = velocity;
	m_rotVelocity = rotVelocity;	
}	
void Object::init(const glm::vec2& position, const glm::vec2& size, float rotation, const std::string& texture){
	sprite.init(position, size, rotation, glm::uvec4(255), texture);
	aabb.update(position, size, rotation);
}

void Object::update(float resistanceX, float resistanceY) {
	sprite.position += m_velocity * glm::vec2(FPSRegulator::getDelta());
	sprite.rotation += m_rotVelocity * FPSRegulator::getDelta();

	m_velocity /= glm::vec2(resistanceX, resistanceY);
	m_rotVelocity /= resistanceX;

	aabb.update(sprite.position, sprite.size, sprite.rotation);
}

}
