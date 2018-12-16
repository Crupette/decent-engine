#include "Particle.h"

namespace DecentEngine {

Particle::Particle(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec2& velocity, float rotVelocity, const std::string& texture, float life) : m_life(life){
	object.init(position, size, velocity, rotation, rotVelocity, texture);
}

}
