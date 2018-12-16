#include "FontRenderer.h"
#include "Base.h"

namespace DecentEngine {

Logger FontRenderer::m_logger("FontRenderer");

FontRenderer::FontRenderer() : m_font(nullptr)
{
}


FontRenderer::~FontRenderer()
{
}

void FontRenderer::init(const std::string& path, unsigned int size)
{
	m_size = size;

	if (!TTF_WasInit()) {
		int errorCode = TTF_Init();
		if (errorCode == -1) {
			m_logger.log(Logger::Type::ERROR, "FontRenderer: TTF Failed to initialize. error:", TTF_GetError());
			exit(-1);
		}
	}

	m_font = TTF_OpenFont(path.c_str(), size);
	if (!m_font) {
		m_logger.log(Logger::Type::ERROR, "FontRenderer: TTF Failed to open file:", TTF_GetError());
		exit(-1);
	}

	for (unsigned int i = 0; i < 0x100; i++) {
		int charindex = TTF_GlyphIsProvided(m_font, (char)i);
		if (charindex != 0) {
			m_allGlyphs.emplace((char)i, Glyph());
			Glyph* glyph = &m_allGlyphs.find((char)i)->second;
			TTF_GlyphMetrics(m_font, (char)i, &glyph->minx, &glyph->maxx, &glyph->miny, &glyph->maxy, &glyph->advance);

			SDL_Surface* surface = TTF_RenderGlyph_Blended(m_font, (char)i, SDL_Color{255, 255, 255, 255});

			glyph->width = surface->w;
			glyph->height = surface->h;

			glGenTextures(1, &glyph->texture);
			glBindTexture(GL_TEXTURE_2D, glyph->texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

			//printf("Character %c is provided by font (%i-%i, %i-%i, tid %i)\n", (char)i, glyph->minx, glyph->maxx, glyph->miny, glyph->maxy, glyph->texture);
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	m_batch.init();
}

void FontRenderer::destroy()
{
	TTF_CloseFont(m_font);
	m_font = nullptr;
	TTF_Quit();

	for (auto& it : m_allGlyphs) {
		glDeleteTextures(1, &it.second.texture);
	}
	m_allGlyphs.clear();
	m_batch.destroy();
}

void FontRenderer::setText(const std::string & text, const glm::vec2 & position, const glm::vec2 & scale, const glm::uvec4& color)
{
	m_batch.begin();

	float currX = 0.f;

	float realX = position.x;
	float realY = position.y;

	for (char c : text) {

		if (c == '\n') {
			realY -= TTF_FontHeight(m_font);
			currX = 0.f;
			continue;
		}

		auto it = m_allGlyphs.find(c);
		if (it == m_allGlyphs.end()) {
			m_logger.log(Logger::Type::WARN, "FontRenderer: Failed to render character", c, ": Character is not present in font!");
			continue;
		}

		m_batch.addSprite(glm::vec4(realX + currX, realY , it->second.width * scale.x, it->second.height * scale.y), glm::vec4(0.f, 0.f, 1.f, 1.f), color, 0.f, 0, it->second.texture);

		currX += it->second.advance * scale.x;
	}

	m_batch.end();
}

void FontRenderer::render()
{
	m_batch.renderBatches();
}

void FontRenderer::renderText(const std::string & text, const glm::vec2 & position, const glm::vec2 & scale, const glm::uvec4& color) {
	setText(text, position, scale, color);
	render();
}


}

