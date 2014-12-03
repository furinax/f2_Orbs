#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"

class ParticleG : public Particle{
public:

	ParticleG(const ci::Vec2f& position, const Listener& list);
	void update(const Listener& list, const ci::Vec2f pos);
	void draw(const bool overlay, const Listener& list, const ci::Vec2f pos);
	void addVelocity(const ci::Vec2f& pos, const Listener & list);

	float mVelocityAnchor;
	std::list<ci::Vec2f> mVelocities;
};