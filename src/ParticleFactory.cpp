#include "ParticleFactory.h"

using namespace ci;
using namespace ci::app;

void ParticleFactory::create(const int elapsedSeconds, const Vec2f origin, const Listener& list, ParticleSystem & ps)
{
	ps.mUnderlays = 3;
	switch (d_particleToCreate)
	{
	
	case PARTICLE_A:{
		for (int i = 0; i < 3; ++i)
		{
			Particle* particle = new ParticleA(origin, list);
			particle->mOrientation = ps.mOrientation;
			ps.addParticle(particle);
		}
	}break;
	case PARTICLE_B:{
		Particle* particle = new ParticleB(origin, list);
			ps.addParticle(particle);
	}break;
	case PARTICLE_C:{
		Particle* particle = new ParticleC(origin, list);
			ps.addParticle(particle);
	}break;
	case PARTICLE_D:{
		for (int i = 0; i < (int)(list.getVolume()*20.f); ++i)
		{
			Particle* particle = new ParticleD(origin, list);
			ps.addParticle(particle);
		}
	}break;
	case PARTICLE_E:{
			Particle* particle = new ParticleE(origin, list);
			particle->mOrientation = ps.mOrientation;
			ps.addParticle(particle);
	}break;
	case PARTICLE_F:{
		for (int i = 0; i < 4; ++i)
		{
			Particle* particle = new ParticleF(origin, list);
			particle->mOrientation = ps.mOrientation;
			ps.addParticle(particle);
		}
	}break;
	case PARTICLE_G:{
			while (ps.mParticles.size() < 3)
			{
				Particle* particle = new ParticleG(origin, list);
				ps.addParticle(particle);
			}
	}break;
	case PARTICLE_H:{
		for (int i = 0; i < 4; ++i)
		{
			Particle* particle = new ParticleH(origin, list);
			ps.addParticle(particle);
		}
	}break;
	case PARTICLE_I:{
			Particle* particle = new ParticleI(origin, list);
			ps.addParticle(particle);
	}break;
	case PARTICLE_J:{
		Particle* particle = new ParticleJ(origin, list);
		ps.addParticle(particle);
	}break;
	case PARTICLE_K:{
		Particle* particle = new ParticleK(origin, list);
		ps.addParticle(particle);
	}break;
	case PARTICLE_L:{
		Particle* particle = new ParticleL(origin, list);
		ps.addParticle(particle);
	}break;
	case PARTICLE_M:{
		Particle* particle = new ParticleM(origin, list);
		particle->mOrientation = ps.mOrientation;
		ps.addParticle(particle);
		ps.mUnderlays = 1;
	}break;
	case PARTICLE_N:{
		Particle* particle = new ParticleN(origin, list);
		ps.addParticle(particle);
	}break;
	default:
		ci::app::console() << "UNKNOWN PARTICLE: " << d_particleToCreate;
		break;
	}
}

void ParticleFactory::perform(const int elapsedSeconds, const Vec2f origin, const Listener& list, ParticleSystem & ps)
{
	
	if (elapsedSeconds >= 30 && elapsedSeconds < 45)
	{
		while (ps.mParticles.size() < 3)
		{
			Particle* particle = new ParticleG(origin, list);
			ps.addParticle(particle);
		}
	}
	if (elapsedSeconds >= 45 && elapsedSeconds < 75)
	{
		Particle* particle = new ParticleC(origin, list);
		ps.addParticle(particle);
	}
	if (elapsedSeconds >= 75 && elapsedSeconds < 105)
	{
		Particle* particle = new ParticleB(origin, list);
		ps.addParticle(particle);
	}
	if (elapsedSeconds >= 105 && elapsedSeconds < 135)
	{
		Particle* particle = new ParticleN(origin, list);
		ps.addParticle(particle);
	}
	if (elapsedSeconds >= 135 && elapsedSeconds < 150)
	{
		Particle* particle = new ParticleI(origin, list);
		ps.addParticle(particle);
	}
	if (elapsedSeconds >= 135 && elapsedSeconds < 165)
	{
		for (int i = 0; i < (int)(list.getVolume()*10.f); ++i)
		{
			Particle* particle = new ParticleD(origin, list);
			ps.addParticle(particle);
		}
		for (int i = 0; i < 3; ++i)
		{
			Particle* particle = new ParticleA(origin, list);
			particle->mOrientation = ps.mOrientation;
			ps.addParticle(particle);
		}
	}
	if (elapsedSeconds >= 165 && elapsedSeconds < 195)
	{
		for (int i = 0; i < 4; ++i)
		{
			Particle* particle = new ParticleH(origin, list);
			ps.addParticle(particle);
		}
	}
	if (elapsedSeconds >= 195 && elapsedSeconds < 210)
	{
		for (int i = 0; i < 4; ++i)
		{
			Particle* particle = new ParticleF(origin, list);
			particle->mOrientation = ps.mOrientation;
			ps.addParticle(particle);
		}
		Particle* particle = new ParticleE(origin, list);
		particle->mOrientation = ps.mOrientation;
		ps.addParticle(particle);
	}
	if (elapsedSeconds >= 210 && elapsedSeconds < 225)
	{
		Particle* particle = new ParticleJ(origin, list);
		ps.addParticle(particle);
	}
	if (elapsedSeconds >= 225 && elapsedSeconds < 255)
	{
		Particle* particle = new ParticleL(origin, list);
		ps.addParticle(particle);
	}
	if (elapsedSeconds >= 255 )
	{
		Particle* particle = new ParticleK(origin, list);
		ps.addParticle(particle);
	}

}