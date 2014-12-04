#include "ParticleM.h"
#include <iterator>
#include <cmath>
#include "cinder/CinderMath.h"
#include "CatmullRom.h"

using namespace ci;
using namespace ci::app;

ParticleM::ParticleM(const Vec2f& position, const Listener& list){
	mMaxPositions = 100;
	mLifespan = 50;

	mDrag = .9f;

	mRadius = 5.f;
	mRadiusAnchor = mRadius;

	mAnchorPosition = position;
	addPosition(mAnchorPosition);

	mColor = ColorA(0.f, 1.f, .7f, 1.f);
	mOverlayColor = ColorA::white();

	mIsCurl = randFloat() > .5f;
}

void ParticleM::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;
	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = mRadiusAnchor * ageMap;

	if (mIsCurl && ageMap < .7f)
	{
		Vec2f curler = mDrag * (mPositions.front() - *std::next(mPositions.begin()));
		curler.rotate(mOrientation * .3);
		addPosition(mPositions.front() + curler);		
	}
	else
	{
		addPosition(pos);
		if (!mIsCurl && ageMap < .7f)
			mIsDead = true;
	}
	
}

void ParticleM::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	ColorA inputColor;
	if (mPositions.size() < 15) //don't want to draw the first few lines, they are jagged
		return;
	if (overlay)
	{
		inputColor = mOverlayColor;
	}
	else
	{
		inputColor = mColor;
	}

	CatmullRom::draw(mPositions, mRadius, 1.f, inputColor);
}