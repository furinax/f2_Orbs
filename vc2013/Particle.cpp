#include "Particle.h"

using namespace ci;
using namespace ci::app;

Perlin Particle::mPerlin;

void Particle::addPosition(const Vec2f& position)
{
	if (mPositions.size() > mMaxPositions)
	{
		mPositions.pop_back();
	}
	mPositions.push_front(position);
}