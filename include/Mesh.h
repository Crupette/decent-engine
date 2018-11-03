#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <vector>

namespace DecentEngine {

/**
 * @brief This class is mainly used for testing purposes. You can safely ignore it. the [SpriteBatch] class is more useful.
 */
class Mesh {
	GLuint m_vao;
	GLuint m_vbo[3];

	size_t m_numVertices = 0;
	GLuint m_texture;

	std::vector<float> tmp_positions;
	std::vector<GLubyte> tmp_colors;
	std::vector<float> tmp_uvs;
public:
	Mesh();
	~Mesh();

	/**
	 * @brief The postInit function must be called after the preInit function
	 */
	void preInit();
	void postInit();
	void destroy();

	void setTexture(GLuint texture) {m_texture = texture;}
	void addVertex(float x, float y, GLubyte r, GLubyte g, GLubyte b, GLubyte a, float u, float v);

	void render();
};

}

#endif
