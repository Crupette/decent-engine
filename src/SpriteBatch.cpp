#include "SpriteBatch.h"

#include <algorithm>
#include <functional>

namespace DecentEngine {

SpriteBatch::SpriteBatch(){

}

SpriteBatch::~SpriteBatch(){

}

void SpriteBatch::init(){
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glGenBuffers(3, m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteBatch::destroy(){
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(3, m_vbo);
}

void SpriteBatch::addSprite(const glm::vec4& bounds, const glm::vec4& uv, const glm::uvec4& color, float rotation, int layer, GLuint texture){
	m_glyphs.emplace_back(bounds, uv, color, rotation, layer, texture);
}

void SpriteBatch::addSprite(const Sprite* sprite) {
	m_glyphs.emplace_back(glm::vec4(sprite->position, sprite->size), glm::vec4(0, 0, 1, 1), sprite->color, sprite->rotation, sprite->priority, sprite->texture);
}

void SpriteBatch::begin(){
	m_batches.clear();

	m_glyphs.clear();
	ptr_glyphs.clear();
}

void SpriteBatch::end(){
	ptr_glyphs.resize(m_glyphs.size());
	for(size_t i = 0; i < m_glyphs.size(); i++){
		ptr_glyphs[i] = &m_glyphs[i];
	}

	std::sort(ptr_glyphs.begin(), ptr_glyphs.end(), [](Glyph* a, Glyph* b) {return a->texture < b->texture; });

	createBatches();

	m_glyphs.clear();
	ptr_glyphs.clear();
}

void SpriteBatch::renderBatches(){
	glBindVertexArray(m_vao);

	for(RenderBatch& batch : m_batches){
		glBindTexture(GL_TEXTURE_2D, batch.texture);

		//printf("Rendering batch %p with %lu size and %u offset. Texture %u\n", &batch, batch.numVertices, batch.offset, batch.texture);

		glDrawArrays(GL_TRIANGLES, batch.offset, batch.numVertices);
	
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindVertexArray(0);
}

void SpriteBatch::createBatches(){
	std::vector<float> positions;
	std::vector<float> uvs;
	std::vector<GLubyte> colors;

	if(m_glyphs.size() == 0) return;
	size_t offset = 0;

	m_batches.emplace_back(0, ptr_glyphs[0]->texture);
	positions.insert(positions.end(), ptr_glyphs[0]->positions.begin(), ptr_glyphs[0]->positions.end());
	uvs.insert(uvs.end(), ptr_glyphs[0]->uvs.begin(), ptr_glyphs[0]->uvs.end());
	colors.insert(colors.end(), ptr_glyphs[0]->colors.begin(), ptr_glyphs[0]->colors.end());

	offset += 6;
	m_batches.back().numVertices = 6;

	//printf("Initial glyph: position %f, %f color %x %x %x %x\n", positions[0], positions[1], colors[0], colors[1], colors[2], colors[3]);

	for(size_t i = 1; i < m_glyphs.size(); i++){
		if(m_batches.back().texture != ptr_glyphs[i]->texture) {
			m_batches.emplace_back(offset, ptr_glyphs[i]->texture);
		}
		positions.insert(positions.end(), ptr_glyphs[i]->positions.begin(), ptr_glyphs[i]->positions.end());
		uvs.insert(uvs.end(), ptr_glyphs[i]->uvs.begin(), ptr_glyphs[i]->uvs.end());
		colors.insert(colors.end(), ptr_glyphs[i]->colors.begin(), ptr_glyphs[i]->colors.end());

		offset += 6;
		m_batches.back().numVertices += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);

	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, positions.size() * sizeof(float), positions.data());

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);

	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(char), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, colors.size() * sizeof(char), colors.data());

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);

	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(float), uvs.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}
