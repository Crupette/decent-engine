#ifndef UTIL_H
#define UTIL_H

namespace DecentEngine {

inline glm::vec2 rotatePoint(const glm::vec2& position, const glm::vec2& origin, float rotation){
	float radians = glm::radians(rotation);
	return glm::vec2(
			origin.x + (position.x - origin.x) * std::cos(radians) - (position.y - origin.y) * std::sin(radians),
			origin.y + (position.x - origin.x) * std::sin(radians) + (position.y - origin.y) * std::cos(radians));
}

inline glm::vec2 getHeading(float rotation){
	float radians = glm::radians(rotation);
	return glm::vec2(std::cos(radians), std::sin(radians));
}


}

#endif
