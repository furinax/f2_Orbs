#include "ParticleFactory.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace
{
	float MAX_PARTICLE_RADIUS = 5.f, MIN_PARTICLE_RADIUS = 2.f;
}
void ParticleFactory::create(const int elapsedSeconds, const Vec2f center, const Listener& list, ParticleSystem & ps)
{
	if (elapsedSeconds<10)
	{
		Particle* particle = new ParticleC(center, ci::constrain(MAX_PARTICLE_RADIUS * list.getVolume() * 5.f, MIN_PARTICLE_RADIUS, MAX_PARTICLE_RADIUS), list);
		ps.addParticle(particle);
	}
	else if (elapsedSeconds < 15)
	{
		Particle* particle = new ParticleB(center, ci::constrain(MAX_PARTICLE_RADIUS * list.getVolume() * 5.f, MIN_PARTICLE_RADIUS, MAX_PARTICLE_RADIUS), list);
		ps.addParticle(particle);
	}
	else
	{
		Particle* particle = new ParticleA(center, ci::constrain(MAX_PARTICLE_RADIUS * list.getVolume() * 5.f, MIN_PARTICLE_RADIUS, MAX_PARTICLE_RADIUS), list);
		ps.addParticle(particle);
	}
}