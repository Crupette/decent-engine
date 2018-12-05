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
	/**
	 * @brief Loads the texture into memory from the pre-given data
	 *
	 * @param data Its a basic_string of unsigned chars because its more efficient somehow.
	 * @param name Name of the texture
	 */
	static void loadTextureFromData(const std::basic_string<unsigned char>& data, const std::string& name);
};

}

#endif
