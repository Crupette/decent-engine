#include "Mesh.h"

namespace DecentEngine {

Mesh::Mesh(){
	
}

Mesh::~Mesh(){

}

void Mesh::preInit(){
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

void Mesh::postInit(){
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, tmp_positions.size() * sizeof(float), tmp_positions.data(), GL_STATIC_DRAW);
	tmp_positions.clear();
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tmp_colors.size() * sizeof(GLubyte), tmp_colors.data(), GL_STATIC_DRAW);
	tmp_colors.clear();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, tmp_uvs.size() * sizeof(float), tmp_uvs.data(), GL_STATIC_DRAW);
	tmp_uvs.clear();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::destroy(){
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(3, m_vbo);
}

void Mesh::render(){
	glBindVertexArray(m_vao);
	
	//TODO: Textures
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	
	glBindVertexArray(0);
}

void Mesh::addVertex(float x, float y, GLubyte r, GLubyte g, GLubyte b, GLubyte a, float u, float v){
	m_numVertices++;
	tmp_positions.push_back(x);
	tmp_positions.push_back(y);

	tmp_colors.push_back(r);	
	tmp_colors.push_back(g);
	tmp_colors.push_back(b);
	tmp_colors.push_back(a);

	tmp_uvs.push_back(u);
	tmp_uvs.push_back(v);
}

}
