#include "ParticleEngine.h"
#include "RendererDefault.h"

namespace DecentEngine {

std::vector<Particle*> ParticleEngine::m_particles;
Camera* ParticleEngine::m_camera;

void ParticleEngine::destroy(){
	for(size_t i = 0; i < m_particles.size(); i++){
		delete m_particles[i];
	}
}

void ParticleEngine::update(){
	for(size_t i = 0; i < m_particles.size(); i++){
		if(m_particles[i]->update()){
			m_particles.erase(m_particles.begin() + i);
		}
	}
}

void ParticleEngine::render(){
	RendererDefault::begin(*m_camera);

	for(Particle* particle : m_particles){
		RendererDefault::addObject(&(particle->object));
	}

	RendererDefault::end();
}

void ParticleEngine::useCamera(Camera* camera){
	m_camera = camera;
}

void ParticleEngine::addParticle(Particle* particle){
	m_particles.emplace_back(particle);
}

}
