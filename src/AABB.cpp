#include "AABB.h"
#include "Util.h"

namespace DecentEngine {

AABB::AABB() : m_bounds(0), m_center(0){}
AABB::AABB(const glm::vec2& position, const glm::vec2& size, float rotation) : m_bounds(position, size), m_center(position + glm::vec2(size.x / 2.f, size.y / 2.f)) {
	update(rotation);		
}
AABB::AABB(const glm::vec4& bounds, float rotation) : m_bounds(bounds), m_center(glm::vec2(bounds.x + (bounds.z / 2.f), bounds.y + (bounds.w / 2.f))) {
	update(rotation);
}

void AABB::update(const glm::vec2& position, const glm::vec2& size) {
	m_bounds = glm::vec4(position, size);
	m_center = position + glm::vec2(size.x / 2.f, size.y / 2.f);
}

void AABB::update(const glm::vec4& bounds) {
	m_bounds = bounds;
	m_center = glm::vec2(bounds.x + (bounds.z / 2.f), bounds.y + (bounds.w / 2.f));
}

void AABB::update(const glm::vec2& position, const glm::vec2& size, float rotation) {
	update(position, size);
	update(rotation);
}

void AABB::update(const glm::vec4& bounds, float rotation) {
	update(bounds);
	update(rotation);
}

void AABB::update(float rotation) {
	if(std::fmod(rotation, 360.f) != 0.f){
		glm::vec2 half(m_bounds.z / 2.f, m_bounds.w / 2.f);

		glm::vec2 br(half.x, -half.y);
		glm::vec2 tr(half.x, half.y);

		br = rotatePoint(br, glm::vec2(0), rotation);
		tr = rotatePoint(tr, glm::vec2(0), rotation);

		half = glm::vec2(std::max(std::abs(br.x), std::abs(tr.x)), std::max(std::abs(br.y), std::abs(tr.y)));

		m_bounds = glm::vec4(m_center.x - half.x, m_center.y - half.y, half.x * 2, half.y * 2);
	}
}
//STATIC
bool AABB::check(const AABB& a, const AABB& b){
	glm::vec4 abounds = a.getBounds();
	glm::vec4 bbounds = b.getBounds();
	if(abounds.x < bbounds.x + bbounds.z &&
	   abounds.x + abounds.z > bbounds.x &&
	   abounds.y < bbounds.y + bbounds.w &&
	   abounds.y + abounds.w > bbounds.y) {
		return true;
	}
	return false;

}

}
