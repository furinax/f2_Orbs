#include "ParticleB.h"
#include <iterator>

using namespace ci;
using namespace ci::app;

ParticleB::ParticleB(const Vec2f& position, const Listener &list){
	mAnchorPosition = getWindowCenter();

	mRadius = 100.f*list.getVolume();
	mRadiusAnchor = 3.f;

	float listSquared = list.getVolume() * list.getVolume();
	mFillGaps = true;
	mColor = Color(listSquared, .4f*listSquared, 1.f - listSquared);
	mOverlayColor = Color::white();
	mDrag = 1.5f;
	mLifespan = 5;
}

void ParticleB::update(const Listener& list, const ci::Vec2f pos){

	mAge++;
	if (mAge > mLifespan)
		mIsDead = true;

	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius *= mDrag;

}

void ParticleB::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		gl::color(mOverlayColor);
	}
	gl::lineWidth(mRadiusAnchor);
	gl::drawStrokedCircle(getWindowCenter(), mRadius);

}