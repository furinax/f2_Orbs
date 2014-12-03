#include "ParticleL.h"
#include <iterator>
#include <cmath>
#include "cinder/CinderMath.h"
#include "CatmullRom.h"

using namespace ci;
using namespace ci::app;

ParticleL::ParticleL(const Vec2f& position, const Listener& list){
	mMaxPositions = 10;
	mLifespan = 20;

	mRadius = 1.f;
	mRadiusAnchor = mRadius;

	mAnchorPosition = position - getWindowCenter();
	addPosition(mAnchorPosition);

	mColor = ColorA(.3f, .5f, 1.f, 1.f);
	mOverlayColor = ColorA::white();
}

void ParticleL::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;
	float ageMap = 1.0f - (mAge / (float)mLifespan);

	mRadius = constrain(list.getVolume() * 2.f, .5f, 2.f );
	
	Vec2f expander = mAnchorPosition;
	expander.rotate(mAge/20.f);
	expander *= mRadius;
	addPosition( expander );
}

void ParticleL::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	ColorA inputColor;
	if (overlay)
	{
		inputColor = mOverlayColor;
	}
	else
	{
		inputColor = mColor;
	}
	gl::pushMatrices();
	gl::translate(getWindowCenter());
	CatmullRom::draw(mPositions, 3.f, .8f, inputColor);
	gl::popMatrices();
}