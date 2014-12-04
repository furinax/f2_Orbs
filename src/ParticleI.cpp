#include "ParticleI.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleI::ParticleI(const Vec2f& position, const Listener& list){
	addPosition(Vec2f::zero());
	addPosition(Vec2f::zero());
	mAnchorPosition = position;

	mRadius = list.getVolume() * 25;
	mRadiusAnchor = mRadius;

	mOverlayColor = Color::white();
	mDrag = .8f;

	mFillGaps = false;
	mVelThreshold = 5.f;
	mVel = randVec2f() * 40.f;
	mColor = ColorA(1.f, .4f, 0.6f, 1.f);

}

void ParticleI::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;
	//mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);
	mLineWidth = 5.f * ageMap;

	Vec2f newPos = Vec2f(mPositions.front());
	mVel += mAcc;
	float noise = mPerlin.fBm(Vec3f(newPos * 0.005f, app::getElapsedSeconds() * 0.1f));
	float angle = noise * 15.0f;
	mVel += Vec2f(cos(angle), sin(angle)) * 20.f * (1.0f - ageMap);
	mVel *= mDrag;
	newPos += mVel;
	addPosition(newPos);
}

void ParticleI::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	gl::pushMatrices();
	gl::translate(mAnchorPosition);
	gl::lineWidth(mLineWidth);
	gl::drawStrokedCircle(mPositions.front(), mRadius);
	
	gl::popMatrices();
}