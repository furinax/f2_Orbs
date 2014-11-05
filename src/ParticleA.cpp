#include "ParticleA.h"

using namespace ci;
using namespace std;
using namespace ci::app;

//sparks that fly out in a spiral

ParticleA::ParticleA(const Vec2f& position, const float radius, const Listener& list){
	this->position = position;
	this->anchorPosition = position;
	this->mRadiusAnchor = radius;
	this->mRadius = radius;
	//this->VEL_THRESHOLD = radius * 2;
	prevPosition = position;
	mColor = Color::white();
	mOverlayColor = Color::white();
	mDrag = 1.0f;

	this->mVel = 20.f*(Vec2f(sin(getElapsedFrames() / 4.f), cos(getElapsedFrames() / 4.f)));
	float x = constrain(2.f* list.getVolume(), 0.f, 1.f);
	this->mColor = ColorA(randFloat(), x / 2.f, 1.f - x, 1.f);

}

void ParticleA::update(const Listener& list, const ci::Vec2f pos){

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

void ParticleA::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	if ( mVel.length() > VEL_THRESHOLD)
	{
		gl::lineWidth(mRadius * 2);
		gl::begin(GL_LINES);
		gl::vertex(prevPosition);
		gl::vertex(position);
		gl::end();
		gl::drawSolidCircle(position, mRadius);
		gl::drawSolidCircle(prevPosition, mRadius);
	}
	else
	{
		gl::drawSolidCircle(position, mRadius);
	}
}