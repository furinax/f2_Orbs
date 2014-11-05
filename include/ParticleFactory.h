#pragma once

#include "Particle.h"
#include "ParticleA.h"
#include "ParticleB.h"
#include "ParticleC.h"
#include "Listener.h"
#include "ParticleSystem.h"

#include "cinder/app/AppNative.h"

class ParticleFactory
{
public:
	void create(const int elapsedSeconds, const ci::Vec2f center, const Listener& list, ParticleSystem & ps);
};