#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/AppNative.h"
#include "cinder/Rand.h"
#include "Listener.h"

class Particle{
public:
    
	virtual void update(const Listener& list, const ci::Vec2f pos) = 0;
	virtual void draw(const bool overlay, const Listener& list, const ci::Vec2f pos) = 0;
    
    ci::Vec2f position, prevPosition, anchorPosition;
	ci::Vec2f mVel, mAcc;
    float mRadiusAnchor, mRadius, mDrag;
	int mAge = 0, mLifespan = 20;
	bool mIsDead = false;
	ci::ColorA mColor, mOverlayColor;

	float VEL_THRESHOLD = 15.f; //threshold of vel to determine when to draw a line
};