/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-12-15
 *	Compiler:		gcc -std=c++17
 * */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "Object.h"

namespace DecentEngine {

class Particle {
protected:
	float m_life;
public:
	Particle(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec2& velocity, float rotVelocity, const std::string& texture, float life);
	virtual ~Particle() {}

	virtual bool update() = 0;

	Object object;
};

}

#endif
