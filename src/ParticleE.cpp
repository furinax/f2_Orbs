#include "ParticleE.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleE::ParticleE(const Vec2f& position, const Listener& list){
	mMaxPositions = 1;
	addPosition(Vec2f::zero());
	mAnchorPosition = getWindowCenter();

	mRadius = list.getVolume() * 10.f;
	mRadiusAnchor = mRadius;

	mOverlayColor = Color::white();
	mDrag = 1.f;
	mLifespan = 200;

	mFillGaps = false;
	mVelThreshold = 5.f;
	mVel = Vec2f::one() * 10.f;
	mColor = ColorA(1.f, 1.f, 0.f, 1.f);

}

void ParticleE::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);

	mRadius = mRadiusAnchor * ageMap;
	//mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);


	Vec2f newPos = Vec2f(mPositions.front());
	mAcc = Vec2f(0, 1.f) * sin(getElapsedSeconds());
	mVel += mAcc;
	mVel *= mDrag;
	newPos += mVel;
	addPosition(newPos);
}

void ParticleE::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	gl::pushMatrices();
	gl::translate(mAnchorPosition);
	gl::rotate(mOrientation * 90 + 13);
	gl::drawSolidCircle(mPositions.front(), mRadius);
	gl::rotate(90);
	gl::drawSolidCircle(mPositions.front(), mRadius);
	gl::popMatrices();
}