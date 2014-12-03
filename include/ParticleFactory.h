#pragma once

#include "Particle.h"
#include "ParticleA.h"
#include "ParticleB.h"
#include "ParticleC.h"
#include "ParticleD.h"
#include "ParticleE.h"
#include "ParticleF.h"
#include "ParticleG.h"
#include "ParticleH.h"
#include "ParticleI.h"
#include "ParticleJ.h"
#include "ParticleK.h"
#include "ParticleL.h"
#include "ParticleM.h"


#include "Listener.h"
#include "ParticleSystem.h"

#include "cinder/app/AppNative.h"

enum particle_choice
{
	PARTICLE_A, // spirals out, neon lights
	PARTICLE_B, // zooms into the anchor point
	PARTICLE_C, // blue splashes that are circular
	PARTICLE_D, // same as c but individual with perlin noise
	PARTICLE_E, // four spokes coming out, following the first point
	PARTICLE_F, // nova of particles
	PARTICLE_G,  //spline tails
	PARTICLE_H,  //sparks
	PARTICLE_I,   //circles
	PARTICLE_J,   //fixed boxes
	PARTICLE_K,   //three legged creatures
	PARTICLE_L,   //spinning particles
	PARTICLE_M,   //branches that curl
};

class ParticleFactory
{
public:
	void create(const int elapsedSeconds, const ci::Vec2f center, const Listener& list, ParticleSystem & ps);
	int d_particleToCreate=10;
};