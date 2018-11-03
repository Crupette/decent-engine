#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <vector>
#include <array>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Util.h"
#include "Sprite.h"

namespace DecentEngine {

class SpriteBatch {
public:
	struct Glyph {
		Glyph(const glm::vec4& bounds, const glm::vec4& uv, const glm::uvec4& color, float rotation, int layer, GLuint texture) : layer(layer), texture(texture) {	
			glm::vec2 origin(bounds.x + bounds.z / 2.f, bounds.y + bounds.w / 2.f);

			glm::vec2 bl = rotatePoint(glm::vec2(bounds.x, bounds.y), origin, rotation);
			glm::vec2 br = rotatePoint(glm::vec2(bounds.x + bounds.z, bounds.y), origin, rotation);
			glm::vec2 tl = rotatePoint(glm::vec2(bounds.x, bounds.y + bounds.w), origin, rotation);
			glm::vec2 tr = rotatePoint(glm::vec2(bounds.x + bounds.z, bounds.y + bounds.w), origin, rotation);

			positions =
			{
				bl.x, bl.y,
				br.x, br.y,
				tl.x, tl.y,
				br.x, br.y,
				tl.x, tl.y,
				tr.x, tr.y
			};
			uvs =
			{
				uv.x, uv.y,
				uv.x + uv.z, uv.y,
				uv.x, uv.y + uv.w,
				uv.x + uv.z, uv.y,
				uv.x, uv.y + uv.w,
				uv.x + uv.z, uv.y + uv.w
			};
			colors = {
				(unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a,
				(unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a,
				(unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a,
				(unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a,
				(unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a,
				(unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a,
			};
		}
		Glyph() {}
		
		std::vector<float> positions;
		std::vector<unsigned char> colors;
		std::vector<float> uvs;

		int layer;
		GLuint texture;
	};

	struct RenderBatch {
		RenderBatch(GLuint offset, GLuint texture) : offset(offset), texture(texture) {}

		GLuint offset;
		GLuint texture;
		size_t numVertices = 0;
	};

	SpriteBatch();
	~SpriteBatch();

	/**
	 * @brief Intializes the OpenGL objects
	 */
	void init();
	/**
	 * @brief Cleans the OpenGL objects
	 */
	void destroy();
	/**
	 * @brief Adds a glyph to to be rendered in the current batch
	 *
	 * @param bounds Dimensions of the sprite. Bottom left corner to top right corner
	 * @param uv UV dimensions. Same as the bounds arg
	 * @param color Color of the sprite. [R, G, B, A]
	 * @param rotation Rotation of the sprite
	 * @param layer Layer to be rendered on. Higher layers get rendered on top of lower layers
	 * @param texture Texture of the sprite. Batches are sorted by texture
	 */
	void addSprite(const glm::vec4& bounds, const glm::vec4& uv, const glm::uvec4& color, float rotation, int layer, GLuint texture);
	/**
	 * @brief Adds a glyph to be rendered in the current batch
	 *
	 * @param sprite Datatype determining the bounds, color, rotation, and texture
	 */
	void addSprite(const Sprite* sprite);
	/**
	 * @brief Cleans the batches
	 */
	void begin();
	/**
	 * @brief Creates the batches and cleans the glyphs. The [renderBatches] function can be called anytime after this
	 */
	void end();
	/**
	 * @brief Renders the batches to the screen
	 */
	void renderBatches();
private:
	std::vector<Glyph> m_glyphs;
	std::vector<Glyph*> ptr_glyphs;

	std::vector<RenderBatch> m_batches;

	GLuint m_vao;
	GLuint m_vbo[3];

	/**
	 * @brief Creates batches based off the given glyphs
	 */
	void createBatches();
};

}

#endif
