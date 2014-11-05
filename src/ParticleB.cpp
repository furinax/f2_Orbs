#include "ParticleB.h"

using namespace ci;
using namespace std;

//white charge that goes towards the cursor

ParticleB::ParticleB(const Vec2f& position, const float radius, const Listener &list){
	Vec2f offset = ci::app::getWindowWidth()*randVec2f();
	this->position = position + offset;
	this->anchorPosition = position;
	this->mRadiusAnchor = 3.f;
	this->mRadius = .5f;
	this->mVel = -.20 * offset;
	prevPosition = position;
	mColor = Color(1.f, 0.f, 0.f);
	mOverlayColor = Color::white();
	mDrag = .9f;
}

void ParticleB::update(const Listener& list, const ci::Vec2f pos){

	mAge+=2;
	if (mAge > mLifespan)
		mIsDead = true;
	if ((position - anchorPosition).length() < 50.f)
		mDrag = .5f;
	float ageMap = 1.0f - (mAge / (float)mLifespan);
	mRadius = ci::lerp(.5f, mRadiusAnchor, 1.0f - ageMap);
	Vec2f temp = position;
	mVel += mAcc;
	mVel *= mDrag;
	position += mVel;
	prevPosition = temp;
}

void ParticleB::draw(const bool overlay, const Listener& list, const ci::Vec2f pos){
	if (!overlay)
		gl::color(mColor);
	else
	{
		gl::color(mOverlayColor);
	}

	if (mVel.length() > VEL_THRESHOLD)
	{
		gl::lineWidth(mRadius * 2);
		gl::begin(GL_LINES);
		gl::vertex(prevPosition);
		gl::vertex(position);
		gl::end();
		gl::drawSolidCircle(position, mRadius);
		gl::drawSolidCircle(prevPosition, mRadius);
	}
	else
	{
		gl::drawSolidCircle(position, mRadius);
	}
}