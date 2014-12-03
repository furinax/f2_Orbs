#include "ParticleD.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleD::ParticleD(const Vec2f& position, const Listener& list){
	addPosition(Vec2f::zero());
	addPosition(Vec2f::zero());
	mAnchorPosition = position;

	mRadius = 5.f;
	mRadiusAnchor = mRadius;

	mOverlayColor = Color::white();
	mDrag = .8f;

	mFillGaps = false;
	mVelThreshold = 5.f;
	mVel = randVec2f() * 40.f;
	mColor = ColorA(1.f, .5f, 0.f, 1.f);

}

void ParticleD::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;
	//mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);


	Vec2f newPos = Vec2f(mPositions.front());
	mVel += mAcc;
	float noise = mPerlin.fBm(Vec3f(newPos * 0.005f, app::getElapsedSeconds() * 0.1f));
	float angle = noise * 15.0f;
	mVel += Vec2f(cos(angle), sin(angle)) * 20.f * (1.0f - ageMap);
	mVel *= mDrag;
	newPos += mVel;
	addPosition(newPos);
}

void ParticleD::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	gl::pushMatrices();
	gl::translate(mAnchorPosition);

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

	gl::popMatrices();
}