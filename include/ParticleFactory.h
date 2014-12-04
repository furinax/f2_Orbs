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
#include "ParticleN.h"

#include "Listener.h"
#include "ParticleSystem.h"

#include "cinder/app/AppNative.h"

enum particle_choice
{
	PARTICLE_A, // spirals out, neon lights
	PARTICLE_B, // circles which go outwards
	PARTICLE_C, // blue splashes that are circular
	PARTICLE_D, // same as c but individual with perlin noise
	PARTICLE_E, // four spokes coming out, following the first point
	PARTICLE_F, // nova of particles
	PARTICLE_G,  //spline tails
	PARTICLE_H,  //sparks
	PARTICLE_I,   //circles
	PARTICLE_J,   //fixed boxes
	PARTICLE_K,   //CMYK blob
	PARTICLE_L,   //mimics a hurricane
	PARTICLE_M,   //branches that curl
	PARTICLE_N,   //sparkler rays
};

class ParticleFactory
{
public:
	//create: for testing
	void create(const int elapsedSeconds, const ci::Vec2f center, const Listener& list, ParticleSystem & ps);
	//perform: for synchronization to a track
	void perform(const int elapsedSeconds, const ci::Vec2f center, const Listener& list, ParticleSystem & ps);
	int d_particleToCreate=7;
};