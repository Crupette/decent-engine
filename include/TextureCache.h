#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <GL/glew.h>

#include <unordered_map>
#include <string>

namespace DecentEngine {

class TextureCache {
	static std::unordered_map<std::string, GLuint> m_textures;

	/**
	 * @brief Loads the texture into memory
	 *
	 * @param filePath Texture path
	 *
	 * @return texture ID (OpenGL object)
	 */
	static GLuint loadTexture(const std::string& filePath);	
public:
	
	/**
	 * @brief Either loads the texture into memory and return the ID or return the ID from cache
	 *
	 * @param filePath Texture path
	 *
	 * @return texture ID (OpenGL object)
	 */
	static GLuint getTexture(const std::string& filePath);
};

}

#endif
