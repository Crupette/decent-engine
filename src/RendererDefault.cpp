#include "RendererDefault.h"
#include "TextureCache.h"

namespace DecentEngine {

ShaderHandler* RendererDefault::m_shader;
SpriteBatch RendererDefault::m_batch;

void RendererDefault::init(){
	m_shader = new ShaderHandler();

	m_shader->addShader(GL_VERTEX_SHADER, "assets/shaders/base.vert");
	m_shader->addShader(GL_FRAGMENT_SHADER, "assets/shaders/base.frag");

	m_shader->buildProgram();

	m_shader->addAttribute("position");
	m_shader->addAttribute("color");
	m_shader->addAttribute("uv");

	m_batch.init();
}

void RendererDefault::destroy(){
	delete m_shader;
	m_batch.destroy();
}

void RendererDefault::begin(Camera& camera){
	m_shader->use();

	camera.loadUniform(m_shader);
	glActiveTexture(GL_TEXTURE0);

	m_batch.begin();
}

void RendererDefault::beginShader(Camera& camera){
	m_shader->use();
	camera.loadUniform(m_shader);
}

void RendererDefault::end(){
	m_batch.end();
	m_batch.renderBatches();

	m_shader->unuse();

}

void RendererDefault::endShader(){
	m_shader->unuse();
}

void RendererDefault::addObject(Object* object, bool renderBB){
	m_batch.addSprite(&(object->sprite));
	if(renderBB){
		m_batch.addSprite(object->aabb.getBounds(), glm::vec4(0.f, 0.f, 1.f, 1.f), glm::uvec4(255, 0, 0, 128), 0.f, 0, TextureCache::getTexture("blank")); 
	}
}

void RendererDefault::addSprite(Sprite* sprite){
	m_batch.addSprite(sprite);
}

}
