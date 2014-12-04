#include "ParticleN.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleN::ParticleN(const Vec2f& position, const Listener& list){
	mMaxPositions = 50;
	mLifespan = 5;

	mDrag = 1.f;

	mRadius = 3.f * list.getVolume(); //size of spaklers
	mRadiusAnchor = mRadius;

	mAnchorPosition = Vec2f::zero();
	Vec2f expander = position - getWindowCenter();
	expander.safeNormalize();
	expander *= 600;
	for (float i = 0; i < mMaxPositions; ++i)
	{
		addPosition(ci::lerp(Vec2f::zero(), expander, i / mMaxPositions + .2f));
	}

	mVel = 10.f * randVec2f();

	mColor = ColorA(1, .4f, 0, 1.f);
	mOverlayColor = ColorA::white();
}

void ParticleN::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;
	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;
	mLineWidth = 5.f * ageMap;

	mVel += mAcc;
	mVel *= mDrag;

	for (auto itor = mPositions.begin(); itor != mPositions.end(); itor++)
	{
		*itor += randVec2f() * 6.f * list.getVolume() ;
	}
	mAnchorPosition += mVel;
}

void ParticleN::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
	{
		gl::color(mColor);
	}
	else
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
	}

	if ((pos - getWindowCenter()).length() > mMinRadius)
	{
		Vec2f expander = pos + mAnchorPosition - getWindowCenter();
		Vec2f limiter = pos + mAnchorPosition - getWindowCenter();
		expander.safeNormalize();
		expander *= mMaxRadius;
		limiter.safeNormalize();
		limiter *= mMinRadius;

		gl::pushMatrices();
		gl::translate(getWindowCenter());
		glLineWidth(mLineWidth);
		glBegin(GL_LINE_STRIP);
		glVertex2f(limiter);
		glVertex2f(expander);
		glEnd();

		if (overlay)
		{
			for (auto itor = mPositions.begin(); itor != mPositions.end(); itor++)
			{
				gl::drawSolidCircle(*itor, mRadius);
			}
		}

		gl::popMatrices();
	}
	else
	{
		glLineWidth(5);
		gl::drawStrokedCircle(getWindowCenter(), mMinRadius);
	}
}