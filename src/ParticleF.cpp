#include "ParticleF.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleF::ParticleF(const Vec2f& position, const Listener& list){
	mMaxPositions = 1;
	addPosition(Vec2f::zero());
	mAnchorPosition = getWindowCenter();

	mRadius = 5 * randFloat();
	mRadiusAnchor = mRadius;

	mOverlayColor = Color::white();
	mDrag = .9f;
	mLifespan = 50;

	mFillGaps = false;
	mVelThreshold = 5.f;
	mVel = list.getVolume() * 150.f * randVec2f();
	mAcc.x = 2.f;

	mColor = ColorA(.1f, 0.f, 1.f, 1.f);

}

void ParticleF::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan )
		mIsDead = true;

	if (!getWindowBounds().contains(mPositions.front() + getWindowCenter()))
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);

	Vec2f newPos = Vec2f(mPositions.front());
	if (mPositions.front().y > 0 )
		mAcc.y = -5.f ;
	else
		mAcc.y = 5.f ;
	mVel += mAcc;
	mVel *= mDrag;
	newPos += mVel;
	addPosition(newPos);

	mColor = ColorA(list.getVolume(), list.getVolume()/2.f, 1.f, 1.f);
}

void ParticleF::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay || pos.distance(mPositions.front()+getWindowCenter()) < 100)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}
	gl::pushMatrices();
	gl::translate(mAnchorPosition);
	gl::rotate(90 * (mOrientation-1));
	gl::drawSolidCircle(mPositions.front(), mRadius);
	gl::popMatrices();
}