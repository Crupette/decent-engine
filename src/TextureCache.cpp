#include "TextureCache.h"
#include "FileManager.h"
#include "picoPNG.h"

namespace DecentEngine {

std::unordered_map<std::string, GLuint> TextureCache::m_textures;

GLuint TextureCache::getTexture(const std::string& filePath){
	auto it = m_textures.find(filePath);

	if(it == m_textures.end()){
		GLuint newTexture = loadTexture(filePath);
		m_textures.emplace(filePath, newTexture);
		return newTexture;
	}else{
		return it->second;
	}
}

void TextureCache::loadTextureFromData(const std::basic_string<unsigned char>& data, const std::string& name){
	GLuint textureId;

	unsigned long width = 1;
	unsigned long height = 1;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_textures.emplace(name, textureId);
}

GLuint TextureCache::loadTexture(const std::string& filePath){
	GLuint textureId;

	unsigned long width = 0;
	unsigned long height = 0;

	std::vector<unsigned char> fileData;
	std::vector<unsigned char> textureData;

	FileManager::dumpFile(filePath, fileData);

	decodePNG(textureData, width, height, fileData.data(), fileData.size());

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textureData[0]);

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;
}

}
