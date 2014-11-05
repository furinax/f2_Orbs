#include "ParticleC.h"

using namespace ci;
using namespace std;
using namespace ci::app;

// blue splash that follows the cursor

ParticleC::ParticleC(const Vec2f& position, const float radius, const Listener& list){
	this->position = Vec2f::zero();
	this->anchorPosition = position;
	this->mRadiusAnchor = radius;
	this->mRadius = radius;
	//this->VEL_THRESHOLD = radius * 2;
	prevPosition = position;
	mColor = Color::white();
	mOverlayColor = Color::white();
	mDrag = .7f;

	this->mVel = Vec2f(40.f, 0)*(1.f+list.getVolume()*2.f);
	this->mColor = ColorA(0, .5f, 1.f, 1.f);

}

void ParticleC::update(const Listener& list, const ci::Vec2f pos){

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

void ParticleC::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	gl::pushMatrices();
	gl::translate(pos);
	int steps = 10;
	for (int i = 0; i < 36; i++)
	{
		gl::drawSolidCircle(position, mRadius);
		gl::rotate(steps);
	}
	gl::popMatrices();
}