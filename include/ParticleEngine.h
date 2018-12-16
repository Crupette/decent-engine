#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include "Particle.h"
#include "Camera.h"

namespace DecentEngine {

class ParticleEngine {
	static std::vector<Particle*> m_particles;
	static Camera* m_camera;
public:
	static void destroy();

	static void update();
	static void render();

	static void useCamera(Camera* camera);

	static void addParticle(Particle* particle);
};

}

#endif
