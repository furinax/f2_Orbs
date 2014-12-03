#include "ParticleK.h"
#include <iterator>
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;

ParticleK::ParticleK(const Vec2f& position, const Listener& list){
	mMaxPositions = 3;
	mLifespan = 10;

	mRadius = 40.f * list.getVolume();
	mRadiusAnchor = .3f * mRadius;

	Vec2f base = Vec2f::one();// randVec2f();
	for (int i = 0; i < mMaxPositions; i++)
	{
		base.rotate(2.f * M_PI / mMaxPositions);
		mPositions.push_back(base);
	}
	
	mAnchorPosition = getWindowCenter();// position; sadly, couldn't find a way to make this look pretty
	mAnchorPosition.y /= 2;
	//mVel = randVec2f() * 40.f * list.getVolume();
	mDrag = .9f;
	mColor = ColorA(1.f, 1.f, 1.f, 1.f);
	mColors.push_back(ColorA(1,1,0,1));
	mColors.push_back(ColorA(0,1,1,1));
	mColors.push_back(ColorA(1,0,1,1));
}

void ParticleK::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;
	float ageMap = 1.0f - (mAge / (float)mLifespan);

	mVel += mAcc;
	mVel *= mDrag;
	mAnchorPosition += mVel;

	for (auto itor = mPositions.begin(); itor != mPositions.end(); ++itor)
	{
		itor->rotate((list.getVolume())/3.f);
	}

	mLineWidth = 5.f*ageMap;
	mRadius *= 1.1f;
	mRadiusAnchor = .3f * mRadius;
}

void ParticleK::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){

	gl::pushMatrices();
	gl::translate(mAnchorPosition);
	if (overlay)
	{
		ColorA w(Color::white(), mColor.a);
		gl::color(w);
		gl::drawSolidCircle(Vec2f::zero(), mRadiusAnchor );
		gl::popMatrices();
		return;
	}

	gl::lineWidth(mLineWidth);

	auto color_itor = mColors.begin();
	for (auto itor = mPositions.begin(); 
		itor != mPositions.end(), color_itor != mColors.end(); 
		itor++, color_itor++)
	{
		gl::color(*color_itor);
		glBegin(GL_LINE_STRIP);
		glVertex2f(Vec2f::zero());
		glVertex2f(*itor * mRadius);
		glEnd();
		gl::drawSolidCircle(*itor, .7f * mRadiusAnchor);
	}

	gl::popMatrices();
}