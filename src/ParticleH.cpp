#include "ParticleH.h"
#include <iterator>
#include "CatmullRom.h"

using namespace ci;
using namespace ci::app;

ParticleH::ParticleH(const Vec2f& position, const Listener& list){
	mMaxPositions = 2;
	addPosition(position);
	mAnchorPosition = getWindowCenter();

	mRadius = 3.f;
	mRadiusAnchor = mRadius;

	mOverlayColor = Color::white();
	mDrag = 1.f;
	mLifespan = 100;

	mFillGaps = true;
	mVelThreshold = 1.f;
	Vec2f expander = position - getWindowCenter();
	expander.safeNormalize();
	mVel = 5 * randVec2f() + 30*expander;
	mAcc = -Vec2f(0.f, -10.f);

	mColor = ColorA(1.f, .7f, 0.f, 1.f);

}

void ParticleH::update(const Listener& list, const ci::Vec2f pos){
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	if (mPositions.front().y < 0 || mPositions.front().y > getWindowHeight())
		mVel.y *= -.8;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;

	Vec2f newPos = Vec2f(mPositions.front());
	mVel += mAcc;
	mVel *= mDrag;
	newPos += mOrientation*mVel;
	addPosition(newPos);
}

void ParticleH::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
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