#include "ParticleC.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleC::ParticleC(const Vec2f& position, const Listener& list){
	addPosition( Vec2f::zero() );
	addPosition( Vec2f::zero() );
	mAnchorPosition = position;

	mRadius = ci::constrain(mMaxRadius * list.getVolume(), mMinRadius, mMaxRadius);
	mRadiusAnchor = mRadius;

	mColor = ColorA(0, .5f, 1.f, 1.f);
	mOverlayColor = Color::white();

	mDrag = .7f;
	mVel = Vec2f(40.f, 0)*(1.f+list.getVolume()*2.f);
	

}

void ParticleC::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;
	//mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);

	Vec2f newPos = Vec2f(mPositions.front());
	mVel += mAcc;
	mVel *= mDrag;
	newPos += mVel;
	addPosition(newPos);
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
	gl::translate(mAnchorPosition);
	gl::rotate(2*mAge);
	int steps = 10;
	for (int i = 0; i < 36; i++)
	{
		gl::drawSolidCircle(mPositions.front(), mRadius);
		gl::rotate(steps);
	}
	gl::popMatrices();
}