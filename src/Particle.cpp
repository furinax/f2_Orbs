#include "Particle.h"

using namespace ci;
using namespace std;

Particle::Particle( const Vec2f& position, float radius ){
    this->position = position;
	this->anchorPosition = position;
    this->mRadiusAnchor = radius;
	this->mRadius = radius;
	//this->VEL_THRESHOLD = radius * 2;
    prevPosition = position;
	mColor = Color::white();
	mOverlayColor = Color::white();
	mDrag = 1.0f;
}

void Particle::update(){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;
	//mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);

    Vec2f temp = position;
	mVel += mAcc;
	mVel *= mDrag;
	position += mVel;
    prevPosition = temp;
}

void Particle::draw(bool overlay){
	if (!overlay)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	if (false)//(mVel.length() > VEL_THRESHOLD)
	{
		gl::lineWidth(mRadius);
		gl::begin(GL_LINES);
		gl::vertex(prevPosition);
		gl::vertex(position);
		gl::end();
	}
	else
	{
		gl::drawSolidCircle(position, mRadius);
	}
}