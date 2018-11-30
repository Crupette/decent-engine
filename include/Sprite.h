gifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <glm/glm.hpp>

#include "TextureCache.h"

namespace DecentEngine {

struct Sprite {
	Sprite() {}
	~Sprite() {}

	void init(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::uvec4& color, const std::string& texture){
		this->position = position;
		this->size = size;
		this->rotation = rotation;
		this->color = color;

		this->texture = TextureCache::getTexture(texture);
	}

	glm::vec2 position;
	glm::vec2 size;
	float rotation;
	glm::uvec4 color;

	GLuint texture;

	int priority = 0;
};

}

#endif
