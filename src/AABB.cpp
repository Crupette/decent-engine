#include "AABB.h"
#include "Util.h"

#include <cmath>

namespace DecentEngine {

AABB::AABB() : m_bounds(0), m_center(0), m_circular(false){}
AABB::AABB(const glm::vec2& position, const glm::vec2& size, float rotation, bool circular) : m_bounds(position, size), m_center(position + glm::vec2(size.x / 2.f, size.y / 2.f)), m_circular(circular) {
	update(rotation);		
}
AABB::AABB(const glm::vec4& bounds, float rotation, bool circular) : m_bounds(bounds), m_center(glm::vec2(bounds.x + (bounds.z / 2.f), bounds.y + (bounds.w / 2.f))), m_circular(circular) {
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
bool AABB::checkRect(const AABB& a, const AABB& b){
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

bool AABB::check(const AABB& a, const AABB& b){
	if(!a.isCircular() && !b.isCircular()) return checkRect(a, b);
	
	glm::vec4 abounds = a.getBounds(), bbounds = b.getBounds();
	glm::vec2 acenter = a.getCenter(), bcenter = b.getCenter();

	if((a.isCircular() && !b.isCircular()) || (!a.isCircular() && b.isCircular())){
		glm::vec4 cbounds = a.isCircular() ? abounds : bbounds;
		glm::vec2 ccenter = a.isCircular() ? acenter : bcenter;
		glm::vec4 rbounds = a.isCircular() ? bbounds : abounds;
		glm::vec2 rcenter = a.isCircular() ? bcenter : acenter;

		glm::vec2 dist(std::abs(ccenter.x - rcenter.x - rbounds.z/2.f), std::abs(ccenter.y - rcenter.y - rbounds.w/2.f));
		if(dist.x > (rbounds.z/2.f + cbounds.z/2.f) || dist.y > (rbounds.w/2.f + cbounds.w/2.f)) return false;
		if(dist.x < (rbounds.z/2.f) || dist.y < (rbounds.w/2.f)) return true;

		glm::vec2 p_dist(dist.x - rbounds.z/2.f, dist.y - rbounds.w/2.f);
		return (p_dist.x*p_dist.x + p_dist.y*p_dist.y < (cbounds.z*cbounds.w));
	}else{
		glm::vec2 dist(acenter.x - bcenter.x, acenter.y - bcenter.y);
		return std::sqrt(dist.x * dist.x + dist.y * dist.y) < abounds.x/2 + bbounds.x/2;
	}
}

}
