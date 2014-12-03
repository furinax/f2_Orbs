#include "ParticleJ.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleJ::ParticleJ(const Vec2f& position, const Listener& list){
	mAnchorPosition = position;
	mAnchorPosition = Vec2i(mAnchorPosition / 50) * 50;

	mRadius = 25;
	mRadiusAnchor = mRadius;

	mOverlayColor = Color::white();

	mFillGaps = false;
	mVelThreshold = 5.f;
	mVel = randVec2f() * 40.f;
	mColor = ColorA(0.f, 1.f, 0.f, 1.f);

}

void ParticleJ::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	//mRadius = mRadiusAnchor * ageMap;
	//mColor = ColorA(1.f, ageMap / 2.f, (1.0f - ageMap), ageMap);
	mLineWidth = 5.f * ageMap;
}

void ParticleJ::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
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
	Rectf rect(-mRadius, -mRadius, mRadius, mRadius);
	gl::drawStrokedRect(rect);
	
	gl::popMatrices();
}