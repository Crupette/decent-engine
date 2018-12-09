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

void Object::testUpdate(float resistanceX, float resistanceY){
	glm::vec2 spritepos = sprite.position;
	spritepos += m_velocity * glm::vec2(FPSRegulator::getDelta());

	aabb.update(sprite.position, sprite.size, sprite.rotation);

}


void Object::getCollisionSide(AABB& other, bool& collideTop, bool& collideRight, bool& collideBottom, bool& collideLeft){
	glm::vec2 cornerSlope(0.f);
	double velocitySlope = m_velocity.y / m_velocity.x;

	glm::vec4 bounds = aabb.getBounds(), otherbounds = other.getBounds();

	if(bounds.x + bounds.z < otherbounds.x){
		collideLeft = true;
		cornerSlope.x = otherbounds.x - (bounds.x + bounds.z);
		if(bounds.y < otherbounds.y + otherbounds.w){
			collideTop = true;
			cornerSlope.y = otherbounds.y + otherbounds.w - bounds.y;
		}else if(bounds.y + bounds.w > otherbounds.y){
			collideBottom = true;
			cornerSlope.y = otherbounds.y - (bounds.y + bounds.w);
		}else{
			return;
		}
	}else if(bounds.x > otherbounds.x + otherbounds.z){
		collideRight = true;
		cornerSlope.x = bounds.x - (otherbounds.x + otherbounds.z);
		if(bounds.y < otherbounds.y + otherbounds.w){
			collideTop = true;
			cornerSlope.y = bounds.y - (otherbounds.y + otherbounds.w);
		}else if(bounds.y + bounds.w > otherbounds.y){
			collideBottom = true;
			cornerSlope.y = bounds.y + bounds.w - otherbounds.y;
		}else {
			return;
		}
	}else{
		if(bounds.y < otherbounds.y + otherbounds.w){
			collideTop = true;
			return;
		}else if(bounds.y + bounds.w > otherbounds.y){
			collideBottom = true;
			return;
		}else{
			return;
		}
	}
	getCollisionSideFromSlope(velocitySlope, cornerSlope.y / cornerSlope.x, collideTop, collideRight, collideBottom, collideLeft);
}

void Object::getCollisionSideFromSlope(double velocitySlope, double cornerSlope, bool& collideTop, bool& collideRight, bool& collideBottom, bool& collideLeft){
	if(collideTop){
		if(collideLeft){
			if(velocitySlope < cornerSlope) { collideLeft = false; } else { collideTop = false; }
		}else if(collideRight){
			if(velocitySlope > cornerSlope) { collideRight = false; } else { collideTop = false; }
		}
	}else if(collideBottom){
		if(collideLeft){
			if(velocitySlope > cornerSlope) { collideLeft = false; } else { collideBottom = false; }
		}else if(collideRight){
			if(velocitySlope < cornerSlope) { collideRight = false; } else { collideBottom = false; }
		}
	}
}

void Object::correctPositionFromCollision(AABB& other, bool& collideTop, bool& collideRight, bool& collideBottom, bool& collideLeft){
	glm::vec2 newPosition = sprite.position;
	if(collideTop){
		newPosition.y = other.getBounds().y - aabb.getBounds().w;
		m_velocity.y = 0;
	}
	if(collideRight){
		newPosition.x = other.getBounds().x + other.getBounds().z;
		m_velocity.x = 0;
	}
	if(collideBottom){
		newPosition.y = other.getBounds().y + other.getBounds().w;
		m_velocity.y = 0;
	}
	if(collideLeft){
		newPosition.x = other.getBounds().x - aabb.getBounds().z;
		m_velocity.x = 0;
	}
	sprite.position = newPosition;
	aabb.update(sprite.position, sprite.size, sprite.rotation);
}

}
