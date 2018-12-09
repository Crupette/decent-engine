/*
 *	Created By:		Jon Santmyer
 *	Date Created:		2018-11-30
 *	Compiler:		g++ -std=c++17
 * */

#ifndef OBJECT_H
#define OBJECT_H

#include "AABB.h"
#include "Sprite.h"

#include <glm/glm.hpp>

namespace DecentEngine {

	/**
	 * @brief Use this as a container for Sprite and AABB, with helpful other functions, methods, and variables
	 */
class Object {
	glm::vec2 m_velocity;
	float m_rotVelocity;
public:
	Object();
	~Object();

	/**
	 * @brief Sets all of the necessary values
	 *
	 * @param position Position of the object
	 * @param size Size of the object
	 * @param velocity Velocity of the object
	 * @param rotation Rotation of the object in degrees
	 * @param rotVelocity Rotation velocity of the object in degres
	 * @param texture Texture of the sprite
	 */
	void init(const glm::vec2& position, const glm::vec2& size, const glm::vec2& velocity, float rotation, float rotVelocity, const std::string& texture);	
	void init(const glm::vec2& position, const glm::vec2& size, float rotation, const std::string& texture);

	/**
	 * @brief Updates the position of the sprite, and the AABB based on new positions and velocities. Updates the rotation and normal velocities by the resistance factors. (default 0)
	 *
	 * @param resistanceX Resistance on the X axis
	 * @param resistanceY Resistance on the Y axis
	 */
	void update(float resistanceX = 1.f, float resistanceY = 1.f);
	void testUpdate(float resistanceX = 1.f, float resistanceY = 1.f);

    	/**
	 * @brief Gets the collided side(s) and puts the results into the passed arguments
	 *
	 * @param other other object to collide with
	 * @param collideTop
	 * @param collideRight
	 * @param collideBottom
	 * @param collideLeft
	 */
	void getCollisionSide(AABB& other, bool& collideTop, bool& collideRight, bool& collideBottom, bool& collideLeft);
	void getCollisionSideFromSlope(double velocitySlope, double cornerSlope, bool& collideTop, bool& collideRight, bool& collideBottom, bool& collideLeft);
	/**
	 * @brief Corrects the position of the object based on the collided side(s) and the collided object
	 *
	 * @param other other object to collide with
	 * @param collideTop
	 * @param collideRight
	 * @param collideBottom
	 * @param collideLeft
	 */
	void correctPositionFromCollision(AABB& other, bool& collideTop, bool& collideRight, bool& collideBottom, bool& collideLeft);
    
	/**
	 * @brief Setters
	 */
	void setPosition(const glm::vec2& position) { sprite.position = position; }
	void setSize(const glm::vec2& size) {sprite.size = size; }
	void setRotation(float rotation) {sprite.rotation = rotation; }

	/**
	 * @brief Translations. All values entered get added to the base
	 */
	void translatePosition(const glm::vec2& position) { sprite.position += position; }
	void translateSize(const glm::vec2& size) {sprite.size += size; }
	void translateRotation(float rotation) {sprite.rotation += rotation; }

	/**
	 * @brief Getters
	 *
	 * @return the value asked for
	 */
	glm::vec2 getPosition() {return sprite.position; }
	glm::vec2 getSize() { return sprite.size; }
	float getRotation() { return sprite.rotation; }

	void setVelocity(const glm::vec2& velocity) { m_velocity = velocity; }
	void setRotationVelocity(float velocity) {m_rotVelocity = velocity; }

	void translateVelocity(const glm::vec2& velocity) { m_velocity += velocity; }
	void translateRotationVelocity(float velocity) {m_rotVelocity += velocity; }

	glm::vec2 getVelocity() { return m_velocity; }
	float getRotationVelocity() { return m_rotVelocity; }

	Sprite sprite;
	AABB aabb;
};

}

#endif
