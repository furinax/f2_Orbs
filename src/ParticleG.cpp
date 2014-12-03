#include "ParticleG.h"
#include <iterator>
#include "CatmullRom.h"

using namespace ci;
using namespace ci::app;

ParticleG::ParticleG(const Vec2f& position, const Listener& list){
	mMaxPositions = 10;
	addPosition(position);
	
	mAnchorPosition = position;

	mRadius = 6.f;
	mRadiusAnchor = mRadius;

	mOverlayColor = Color::white();
	mDrag = 1.f;
	mLifespan = 500;

	mFillGaps = false;
	mVelThreshold = 5.f;
	mVel = Vec2f(0,randFloat(20) - 10.f);
	addVelocity(position, list);

	mColor = ColorA(.1f, 0.f, 1.f, 1.f);

}

void ParticleG::addVelocity(const ci::Vec2f& pos, const Listener & list)
{
	Vec2f expander = Vec2f(pos - getWindowCenter());
	expander.safeNormalize();
	Vec2f oscillator = Vec2f(expander);
	oscillator = (cos(180 * mAge) * expander) + .2*expander;
	mVelocities.push_front( list.getVolume() * mVel.y * oscillator);
	mVelocities.resize(mMaxPositions);
}

void ParticleG::update(const Listener& list, const ci::Vec2f pos){
	typedef std::list<Vec2f>::iterator itor_t;
	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	mVel += mAcc;
	mVel *= mDrag;
	for (itor_t itor = mPositions.begin(), vel_itor = mVelocities.begin();
		itor != mPositions.end() && vel_itor != mVelocities.end(); 
		itor++, vel_itor++)
	{
		*itor += (*vel_itor);
	}
	addPosition(pos);
	addVelocity(pos, list);
	
}

void ParticleG::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	ColorA inputColor;
	if (!overlay)
		inputColor = mColor;
	else
	{
		inputColor = mOverlayColor;
	}

	CatmullRom::draw(mPositions, mRadius, .9, inputColor);
}