/*
 *	Made By: 	Jon Santmyer
 *	Creation Date: 	2018-11-30
 *	Compiler:	g++ -std=c++17
 * */

#ifndef AABB_H
#define AABB_H

#include <glm/glm.hpp>

namespace DecentEngine {

class AABB {
	glm::vec4 m_bounds;
	glm::vec2 m_center;
public:
	AABB();
	AABB(const glm::vec2& position, const glm::vec2& size, float rotation);
	AABB(const glm::vec4& bounds, float rotation);
	~AABB() {}

	/**
	 * @brief Updates the position and size of the bounding box without rotations
	 *
	 * @param position Position (bottom left) of the element
	 * @param size Size (bottom left -> top right) of the element
	 */
	void update(const glm::vec2& position, const glm::vec2& size);
	void update(const glm::vec4& bounds);
	/**
	 * @brief Updates the position and size of the bounding box using rotation data
	 *
	 * @param position Position (bottom left) of the element
	 * @param size Size (bottom left -> top right) of the element
	 * @param rotation Rotation of the element in degrees
	 */
	void update(const glm::vec2& position, const glm::vec2& size, float rotation);
	void update(const glm::vec4& bounds, float rotation);
	/**
	 * @brief Resizes the bounds based on rotation of the element
	 *
	 * @param rotation Rotation of the element in degrees
	 */
	void update(float rotation);

	glm::vec4 getBounds() const {return m_bounds; }
	glm::vec2 getCenter() const {return m_center; }

	/**
	 * @brief Returns true if the two AABB's are colliding
	 *
	 * @param a AABB of the first element
	 * @param b AABB of the second element
	 *
	 * @return If they are colliding
	 */
	static bool check(const AABB& a, const AABB& b);		
};

}

#endif
