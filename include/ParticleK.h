#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Particle.h"

class ParticleK : public Particle{
public:

	ParticleK(const ci::Vec2f& position, const Listener& list);
	void update(const Listener& list, const ci::Vec2f pos);
	void draw(const bool overlay, const Listener& list, const ci::Vec2f pos);
	float mLineWidth = 5;
	std::vector<ci::ColorA> mColors;
};