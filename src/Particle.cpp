#include "Particle.h"

using namespace ci;
using namespace std;

Particle::Particle( const Vec2f& position, float radius, float mass, float drag ){
    this->position = position;
    this->mRadiusAnchor = radius;
	this->mRadius = radius;
    this->mass = mass;
    this->drag = drag;
    prevPosition = position;
    forces = Vec2f::zero();
	mColor = ColorA(1,.5,0, 1.f);
}

void Particle::update(){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;
	mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);

    Vec2f temp = position;
    Vec2f vel = ( position - prevPosition ) * drag;
    position += vel + forces / mass;
    prevPosition = temp;
    forces = Vec2f::zero();
}

void Particle::draw(bool whiteout){
	if (!whiteout)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}
    gl::drawSolidCircle( position, mRadius );
}