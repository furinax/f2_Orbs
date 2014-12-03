#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/AppNative.h"
#include "cinder/Rand.h"
#include "cinder/Perlin.h"
#include "Listener.h"
#include <iterator>
#include <list>

class Particle{
public:
    
	virtual void update(const Listener& list, const ci::Vec2f pos) = 0;
	virtual void draw(const bool overlay, const Listener& list, const ci::Vec2f pos) = 0;
	void addPosition(const ci::Vec2f & position);

	std::list<ci::Vec2f> mPositions;
	int mMaxPositions = 2; //keeps track of how many points we want to save.... it works like a queue
    ci::Vec2f mAnchorPosition;
	ci::Vec2f mVel, mAcc;
    float mRadiusAnchor = 2.f, mRadius = 2.f, mDrag = 1.f;
	int mAge = 0, mLifespan = 20;
	bool mIsDead = false;
	bool mFillGaps = false; //should we draw lines when the velocity rises above mVelThreshold?
	float mVelThreshold = 15.f; //threshold of vel to determine when to draw a line
	float mMaxRadius = 5.f, mMinRadius = 2.f;
	ci::ColorA mColor, mOverlayColor;
	static ci::Perlin mPerlin;
	int mOrientation = 1; //used for rotation, angle, etc
};