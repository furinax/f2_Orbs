#include "ParticleA.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleA::ParticleA(const Vec2f& position, const Listener& list){
	addPosition( position );
	addPosition( position );
	mAnchorPosition = position;
	
	mRadius = ci::constrain(list.getVolume() * 5.f, mMinRadius, mMaxRadius);
	mRadiusAnchor = mRadius;
	
	mColor = Color::white();
	mOverlayColor = Color::white();
	mDrag = 1.0f;
	mFillGaps = true;

	mVel = randFloat(20.f, 40.f)*(Vec2f(sin(getElapsedFrames() / 4.f), cos(getElapsedFrames() / 4.f)));
	float x = list.getVolume();
	mColor = ColorA(1.f, x / 2.f, 1.f - x, 1.f);

}

void ParticleA::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;
	//mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);

	Vec2f newPos = Vec2f(mPositions.front());
	mVel += mAcc;
	mVel *= mDrag;
	newPos += mOrientation*mVel;
	addPosition(newPos);
}

void ParticleA::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	if (mFillGaps && mVel.length() > mVelThreshold)
	{
		gl::lineWidth(mRadius * 2);
		gl::begin(GL_LINES);
		gl::vertex(*std::next(mPositions.begin()));
		gl::vertex(mPositions.front());
		gl::end();
		gl::drawSolidCircle(mPositions.front(), mRadius);
		gl::drawSolidCircle(*std::next(mPositions.begin()), mRadius);
	}
	else
	{
		gl::drawSolidCircle(mPositions.front(), mRadius);
	}
}